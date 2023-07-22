#include "pch.h"
#include "Chaos.h"
//File should be used to restore any assembly edits or set any variables to 0 when when game reload (level change, act change, death etc)
void RestoreMain()
{
	if (Tornado_Timer != 0)
	{
		numNearbyTasks = 0;
		TaskArraySize = 0;
		numNearbyTasks = 0;
		numAllowedTasks = 0;
		Tornado_Timer = 0;
	}
	if (g_RotaryEmerald_p != 0)
	{
		FreeTask(g_RotaryEmerald_p);
		g_RotaryEmerald_p = 0;
	}
	WriteData((int*)0x5B56D0, (int)0x69E80575); // restore target_man_exec_nop LoadLevelResults
	WriteData((int*)0x5B56D4, (int)0x57FFE5FE); // restore target_man_exec_nop LoadLevelResults
	WriteData<1>((void*)0x798306, 0x85); // restore Jump auto in the cart
	WriteData<1>((void*)0x7983c4, 0x7C); // restore Jump auto in the cart
}