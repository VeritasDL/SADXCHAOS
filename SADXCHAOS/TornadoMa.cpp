#include "pch.h"
#define DISTANCE_THRESHOLD 1000*1000
task* pTaskPtrList[1024] = { 0 };
taskwk* pTaskTwpList[1024] = { 0 };
task* NearbyPTaskPtrList[1024] = { 0 };
NJS_POINT3 playerPos = { 0,0,0 };
taskwk* nearbyTaskTwpList[1024] = { 0 };
task* nearbyAllowedPTaskList[1024] = { 0 };
int numAllowedTasks = 0;

TaskFuncPtr BlackListNearbyPTaskMainPrtList[] = {
	(TaskFuncPtr)0x634980, //People_Main 
	(TaskFuncPtr)0x4FAE30, //ODolsw
	(TaskFuncPtr)0x40B3D0, //Unknown
	(TaskFuncPtr)0x40B2A0, //Unknown
	(TaskFuncPtr)0x438090, //camera_main
	(TaskFuncPtr)0x49A9B0, //sonic_main
	(TaskFuncPtr)0x461700, //tails_main
	(TaskFuncPtr)0x47A770, //Knux_main
	(TaskFuncPtr)0x48ABF0, //amy_main
	(TaskFuncPtr)0x483430, //gamma_main
	(TaskFuncPtr)0x490A00, //big_main
	(TaskFuncPtr)0x7B40C0, //tikal_main
	(TaskFuncPtr)0x7B4EF0, //eggman_main
	(TaskFuncPtr)0x640850, //SceneChange_Main
	(TaskFuncPtr)0x525060, //SceneChangeEC_Main
	(TaskFuncPtr)0x52D710, //SceneChangeEC2_Main
	(TaskFuncPtr)0x5394F0, //OScenechg
	(TaskFuncPtr)0x545670, //OCScenechg
	(TaskFuncPtr)0x7B0C80, //CScenechanger
	(TaskFuncPtr)0x539220, //ChangeSceneMR
	(TaskFuncPtr)0x4B4940, //Emblem_Main
	(TaskFuncPtr)0x6406C0 //Apart of SceneChange_Main seems to be used as the Main Exec for the SS Transitions? (maybe more? idk yet)
};
size_t BlackListNearbyPTaskMainPrtListSize = LengthOfArray(BlackListNearbyPTaskMainPrtList);
NJS_POINT3 pTaskPosList[1024] = { 0,0,0 };
const NJS_VECTOR upVector = { 0,1,0 };
float SMALL_NUMBER = 0.25;
float rotateSpeed(float dist)
{
	if (dist > 20)
		return (sqrt(dist - 20) + SMALL_NUMBER) / 2;
	else
		return SMALL_NUMBER;
}
float moveInSpeed(float dist)
{
	if (dist > 25)
		return sqrt(dist) / 15;
	else
		return max(0, dist - 20) / 15;
}
void multVec(NJS_VECTOR* vec, float scalar)
{
	vec->x *= scalar;
	vec->y *= scalar;
	vec->z *= scalar;
}
void normaliseVec(NJS_VECTOR* vec, float mod)
{
	vec->x /= mod;
	vec->y /= mod;
	vec->z /= mod;
}
float modVec(NJS_VECTOR* vec)
{
	return sqrt(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
}
int TaskArraySize = 0;
int numNearbyTasks = 0;
void TornadoMa()
{
	NJS_VECTOR moveVector = { 0,0,0 };
	NJS_VECTOR distanceVector = { 0,0,0 };
	if (Tornado_Timer == 500)	{
		for (int j = 0; j < 1024; ++j) {
			if (!objStatusEntry[j].pTask) {
				continue;
			}
			if (!objStatusEntry[j].pTask->twp) {
				continue;
			}
			pTaskPtrList[TaskArraySize] = objStatusEntry[j].pTask;
			TaskArraySize++;
		}
		for (int j = 0; j < TaskArraySize; ++j) {
			if (!pTaskPtrList[j]->twp) {
				continue;
			}
			pTaskTwpList[j] = pTaskPtrList[j]->twp;
		}
		for (int i = 0; i < TaskArraySize; i++)	{
			playerPos = playertwp[0]->pos;
			taskwk* task = pTaskTwpList[i];
			if (!task) continue;
			NJS_POINT3 taskPos = task->pos;
			float dx = taskPos.x - playerPos.x;
			float dy = taskPos.y - playerPos.y;
			float dz = taskPos.z - playerPos.z;
			float distance = dx * dx + dy * dy + dz * dz;
			if (distance < DISTANCE_THRESHOLD) {
				nearbyTaskTwpList[numNearbyTasks] = pTaskTwpList[i];
				NearbyPTaskPtrList[numNearbyTasks] = pTaskPtrList[i];
				numNearbyTasks++;
			}
		}
		for (int i = 0; i < numNearbyTasks; i++) {
			task* task = NearbyPTaskPtrList[i];
			if (!task) continue;
			bool isBlacklisted = false;
			for (UINT32 j = 0; j < BlackListNearbyPTaskMainPrtListSize; j++) {
				if (task->exec == BlackListNearbyPTaskMainPrtList[j]) {
					isBlacklisted = true;
					break;
				}
			}
			if (!isBlacklisted) {
				nearbyAllowedPTaskList[numAllowedTasks] = task;
				numAllowedTasks++;
			}
		}
		Tornado_Timer--;
	}
	if (Tornado_Timer < 500 && Tornado_Timer != 0) {
		int a = 1;
		int b = 1;
		for (int i = 0; i < numAllowedTasks; i++) {
			if (!nearbyAllowedPTaskList[i]->twp) {
				continue;
			}
			playerPos = playertwp[0]->pos;
			taskwk* task = nearbyAllowedPTaskList[i]->twp;
			distanceVector.x = playerPos.x - task->pos.x;
			distanceVector.y = playerPos.y - task->pos.y;
			distanceVector.z = playerPos.z - task->pos.z;
			crossProduct(&distanceVector, &upVector, &moveVector);
			normaliseVec(&moveVector, modVec(&moveVector));
			float distance = modVec(&distanceVector);
			multVec(&distanceVector, moveInSpeed(distance) / distance);
			multVec(&moveVector, rotateSpeed(distance));
			njAddVector(&moveVector, &distanceVector);
			njAddVector(&task->pos, &moveVector);
			//DisplayDebugStringFormatted(NJM_LOCATION(0, 9), " %d", TaskArraySize);
			PrintDebug("last edited task: %X \n", (int)NearbyPTaskPtrList[i]); //switched from NearbyPTaskPtrList to nearbyAllowedPTaskList temp.walker need to disable before release
		}
	}
}
task* CurrentpTaskPtrList[1024] = { 0 };
int CurrentTaskArraySize = 0;
void TaskMa()
{
	//count all tasks' with valid twp
	for (int j = 0; j < 1024; ++j) {
		if (!objStatusEntry[j].pTask) {
			continue;
		}
		if (!objStatusEntry[j].pTask->twp) {
			continue;
		}
		CurrentpTaskPtrList[CurrentTaskArraySize] = objStatusEntry[j].pTask;
		CurrentTaskArraySize++;
		taskmatimer = 41;
	}
}