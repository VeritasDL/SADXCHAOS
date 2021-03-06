#include "pch.h"
#include "Chaos.h"
//Rotate Ma Balls - Ha Got em Again!
//Credits to Speeps for all of this Code, Check out Her Github https://github.com/SPEEPSHighway Or Her Meme Maker Mod https://github.com/SPEEPSHighway/MemeMaker
int burgerManSpawned = 0;
int TestSpawned = 0;
RotaryEmeraldWork* rEmeWk;
task* g_RotaryEmerald_p;
task* BURGER1;
task* BURGER2;
task* BURGER3;
task* BURGER4;
task* BURGER5;
task* BURGER6;
task* BURGER7;
NJS_ACTION burgerRing{};
float g_RotaryCircleR = 50.0f;
const int g_EmeraldDTheta[7] = { 0, 0x2492, 0x4924, 0x6DB6, 0x9249, 0xB6DB, 0xDB6D };
int g_EmeraldRotSpd = 0x56;
FunctionPointer(void, effect_create2, (task* obj, int ef_num, float ef_x, float ef_y, float ef_z, NJS_TEXLIST* ef_name), 0x6ED770);
FunctionPointer(void, effect_scl, (int ef_num, float sx, float sy), 0x6ED8E0);
FunctionPointer(void, effect_color, (__int16 ef_num, float col_a, float col_r, float col_g, float col_b), 0x6ED910);
FunctionPointer(void, effect_delete, (__int16 ef_num), 0x6ED490);
void __cdecl SetEffectRotaryEmerald(int eme_num, NJS_TEXLIST* ef_name, float scale, float col_a, float col_r, float col_g, float col_b)
{
	task* obj;
	RotaryEmeraldWork* rEmeWk;
	rEmeWk = (RotaryEmeraldWork*)g_RotaryEmerald_p->twp->value.ptr;
	obj = rEmeWk->eme_task_p[eme_num - 1];
	if (obj)
	{
		effect_create2(obj, eme_num - 1, 0.0f, 0.0f, 0.0f, ef_name);
		effect_scl(eme_num - 1, scale, scale);
		effect_color(eme_num - 1, col_a, col_r, col_g, col_b);
	}
}
void __cdecl SplashRotaryEmerald(float splash_spd)
{
	taskwk* twp;
	float circle;
	twp = g_RotaryEmerald_p->twp;
	circle = 1.0f / g_RotaryCircleR;
	RotaryEmeraldWork* rEmeWk;
	rEmeWk = (RotaryEmeraldWork*)g_RotaryEmerald_p->twp->value.ptr;
	for (int i = 0; i < 7; i++) 
	{
		rEmeWk->eme_spd[i].y = playertwp[0]->pos.y + 10.0f;
		rEmeWk->eme_spd[i].x = (rEmeWk->eme_pos[i].x - playertwp[0]->pos.x) * circle * splash_spd;
		rEmeWk->eme_spd[i].z = (rEmeWk->eme_pos[i].z - playertwp[0]->pos.z) * circle * splash_spd;
	}
	twp->mode = 2;
}
void __cdecl execRotaryEmeraldTask(task* tp)
{
	taskwk* twp;
	RotaryEmeraldWork* rEmeWk;
	twp = tp->twp;
	rEmeWk = (RotaryEmeraldWork*)twp->value.ptr;
	switch (twp->mode) {
	case 0:
		twp->mode = 1;
		break;
	case 1:
		rEmeWk->base_theta += g_EmeraldRotSpd;
		for (int i = 0; i < 7; i++) 
		{
			rEmeWk->eme_theta[i] = g_EmeraldDTheta[i] + rEmeWk->base_theta;
			rEmeWk->eme_pos[i].x = njCos(rEmeWk->eme_theta[i]) * g_RotaryCircleR + playertwp[0]->pos.x;
			rEmeWk->eme_pos[i].y = playertwp[0]->pos.y + 10.0f;
			rEmeWk->eme_pos[i].z = njSin(rEmeWk->eme_theta[i]) * g_RotaryCircleR + playertwp[0]->pos.z;
			if (rEmeWk->eme_task_p[i]) 
			{
				rEmeWk->eme_task_p[i]->twp->pos = rEmeWk->eme_pos[i];
			}
		}
		break;
	case 2:
		for (int i = 0; i < 7; i++) 
		{
			rEmeWk->eme_pos[i].x += rEmeWk->eme_spd[i].x;
			rEmeWk->eme_pos[i].y += rEmeWk->eme_spd[i].y;
			rEmeWk->eme_pos[i].z += rEmeWk->eme_spd[i].z;
			if (rEmeWk->eme_task_p[i])
			{
				rEmeWk->eme_task_p[i]->twp->pos = rEmeWk->eme_pos[i];
			}
		}
		break;
	}
}
void __cdecl destRotaryEmeraldTask(task* tp)
{
	RotaryEmeraldWork* rEmeWk;
	rEmeWk = (RotaryEmeraldWork*)tp->twp->value.ptr;
	for (int i = 0; i < 7; i++)
	{
		effect_delete(i);
		//FreeMemory(BURGER[i]);
	}
	if (rEmeWk)
	{
		FreeMemory(rEmeWk);
		
	}
}
void __cdecl deleteRotaryEmeraldTask()
{
	if (g_RotaryEmerald_p)
	{
		if (g_RotaryEmerald_p->twp == 0x0)
		{
			return;
		}
		rEmeWk = (RotaryEmeraldWork*)g_RotaryEmerald_p->twp->value.ptr;
		for (int i = 0; i < 6; i++) 
		{
			if (rEmeWk->eme_task_p[i])
			{
				effect_delete(i);
			}
		}
		FreeTask(g_RotaryEmerald_p);
		g_RotaryEmerald_p = 0;
	}
}
void __cdecl initRotaryEmeraldTask(task* tp)
{
	tp->exec = execRotaryEmeraldTask;
	tp->disp = 0;
	tp->dest = destRotaryEmeraldTask;
}

void __cdecl createRotaryEmeraldTask(float pos_x, float pos_y, float pos_z, task** eme_task_p)
{
	taskwk* twp;
	g_RotaryEmerald_p = CreateElementalTask(2, 5, initRotaryEmeraldTask);
	rEmeWk = (RotaryEmeraldWork*)AllocateMemory(0xE4);
	twp = g_RotaryEmerald_p->twp;
	twp->pos.x = pos_x;
	twp->pos.y = pos_y;
	twp->pos.z = pos_z;
	twp->value.ptr = rEmeWk;
	twp->mode = 0;
	rEmeWk->base_theta = 0;
	for (int i = 0; i < 7; i++) 
	{
		rEmeWk->eme_task_p[i] = eme_task_p[i];
		rEmeWk->eme_theta[i] = g_EmeraldDTheta[i] + rEmeWk->base_theta;
		rEmeWk->eme_pos[i].x = njCos(rEmeWk->eme_theta[i]) * g_RotaryCircleR + playertwp[0]->pos.x;
		rEmeWk->eme_pos[i].y = playertwp[0]->pos.y + 10.0f;
		rEmeWk->eme_pos[i].z = njSin(rEmeWk->eme_theta[i]) * g_RotaryCircleR + playertwp[0]->pos.z;
	}
}
void __cdecl CreateRotaryEmerald(float pos_x, float pos_y, float pos_z, float r, int rot_spd, task* eme1_task_p, task* eme2_task_p, task* eme3_task_p, task* eme4_task_p, task* eme5_task_p, task* eme6_task_p, task* eme7_task_p)
{
	task* eme_task_p[7]{};
	g_RotaryCircleR = r;
	g_EmeraldRotSpd = rot_spd;
	eme_task_p[0] = eme1_task_p;
	eme_task_p[1] = eme2_task_p;
	eme_task_p[2] = eme3_task_p;
	eme_task_p[3] = eme4_task_p;
	eme_task_p[4] = eme5_task_p;
	eme_task_p[5] = eme6_task_p;
	eme_task_p[6] = eme7_task_p;
	createRotaryEmeraldTask(pos_x, pos_y, pos_z, eme_task_p);
}
void BurgerManSpin()
{
	if (!BurgerSpinTextLoader)
	{
		LoadPVM("SS_PEOPLE", ADV00_TEXLISTS[6]);
		BurgerSpinTextLoader = true;
	}
	if (burgerManSpawned == 0)
	{
		burgerRing.object = MODEL_SS_PEOPLE_OBJECTS[12];
		burgerRing.motion = SS_PEOPLE_MOTIONS[19];
		EV_CreateObject(&BURGER1,playertwp[0]->pos.x + 10.0f,playertwp[0]->pos.y + 10.0f,playertwp[0]->pos.z,0, 0, 0);
		EV_CreateObject(&BURGER2,playertwp[0]->pos.x + 10.0f,playertwp[0]->pos.y + 10.0f,playertwp[0]->pos.z,0, 0, 0);
		EV_CreateObject(&BURGER3,playertwp[0]->pos.x + 10.0f,playertwp[0]->pos.y + 10.0f,playertwp[0]->pos.z,0, 0, 0);
		EV_CreateObject(&BURGER4,playertwp[0]->pos.x + 10.0f,playertwp[0]->pos.y + 10.0f,playertwp[0]->pos.z,0, 0, 0);
		EV_CreateObject(&BURGER5,playertwp[0]->pos.x + 10.0f,playertwp[0]->pos.y + 10.0f,playertwp[0]->pos.z,0, 0, 0);
		EV_CreateObject(&BURGER6,playertwp[0]->pos.x + 10.0f,playertwp[0]->pos.y + 10.0f,playertwp[0]->pos.z,0, 0, 0);
		EV_CreateObject(&BURGER7,playertwp[0]->pos.x + 10.0f,playertwp[0]->pos.y + 10.0f,playertwp[0]->pos.z,0, 0, 0);
		EV_SetMode(BURGER1, 0);
		EV_SetMode(BURGER2, 0);
		EV_SetMode(BURGER3, 0);
		EV_SetMode(BURGER4, 0);
		EV_SetMode(BURGER5, 0);
		EV_SetMode(BURGER6, 0);
		EV_SetMode(BURGER7, 0);
		EV_SetAction((task*)BURGER1, &burgerRing, ADV00_TEXLISTS[6], 0.0f, 1, 0);
		EV_SetAction((task*)BURGER2, &burgerRing, ADV00_TEXLISTS[6], 0.0f, 1, 0);
		EV_SetAction((task*)BURGER3, &burgerRing, ADV00_TEXLISTS[6], 0.0f, 1, 0);
		EV_SetAction((task*)BURGER4, &burgerRing, ADV00_TEXLISTS[6], 0.0f, 1, 0);
		EV_SetAction((task*)BURGER5, &burgerRing, ADV00_TEXLISTS[6], 0.0f, 1, 0);
		EV_SetAction((task*)BURGER6, &burgerRing, ADV00_TEXLISTS[6], 0.0f, 1, 0);
		EV_SetAction((task*)BURGER7, &burgerRing, ADV00_TEXLISTS[6], 0.0f, 1, 0);
		CreateRotaryEmerald(PlayerPtrs[0]->Data1->Position.x, PlayerPtrs[0]->Data1->Position.y + 10.0f, PlayerPtrs[0]->Data1->Position.z, 10.0f, 800,BURGER1,BURGER2,BURGER3,BURGER4,BURGER5,BURGER6,BURGER7);
		//SetEffectRotaryEmerald(1, &ev_effect_list19, 0.5, 1.0, 1.0, 0.0, 0.0); //Used for the Colored Orbs
		//SetEffectRotaryEmerald(2, &ev_effect_list19, 0.5, 1.0, 0.0, 1.0, 0.0); //Used for the Colored Orbs
		//SetEffectRotaryEmerald(3, &ev_effect_list19, 0.5, 1.0, 1.0, 1.0, 1.0); //Used for the Colored Orbs
		//SetEffectRotaryEmerald(4, &ev_effect_list19, 0.5, 1.0, 1.0, 1.0, 0.0); //Used for the Colored Orbs
		//SetEffectRotaryEmerald(5, &ev_effect_list19, 0.5, 1.0, 1.0, 0.0, 1.0); //Used for the Colored Orbs
		//SetEffectRotaryEmerald(6, &ev_effect_list19, 0.5, 1.0, 0.0, 1.0, 1.0); //Used for the Colored Orbs
		//SetEffectRotaryEmerald(7, &ev_effect_list19, 0.5, 1.0, 0.0, 0.0, 1.0); //Used for the Colored Orbs
		burgerManSpawned = 1;
		TextLoaded = true;
	}
	strcpy_s(LastEffect, 128, "Burger Man Ring");
	BurgerSpin_Timer = 420;
}
void BurgerManSpinDelete()
{
	deleteRotaryEmeraldTask();
	EV_FreeObject(&BURGER1);
	EV_FreeObject(&BURGER2);
	EV_FreeObject(&BURGER3);
	EV_FreeObject(&BURGER4);
	EV_FreeObject(&BURGER5);
	EV_FreeObject(&BURGER6);
	EV_FreeObject(&BURGER7);
	burgerManSpawned = 0;
}
void TestSpin()
{
	LoadPVM("SS_PEOPLE", ADV00_TEXLISTS[6]);
	task* Test[7]{};
	//NJS_ACTION TestRing;
	switch (TestSpawned) {
	case 0:
		for (int i = 0; i < 7; i++)
		{
			EV_CreateObject(&Test[i], playertwp[0]->pos.x + (i * 10.0f), playertwp[0]->pos.y + 10.0f, playertwp[0]->pos.z, 0, 0, 0);
			EV_SetMode(Test[i], 0);
			//TestRing.object = MODEL_SS_PEOPLE_OBJECTS[12]; //Need To Change
			//TestRing.motion = SS_PEOPLE_MOTIONS[19]; //Need To Change
			//EV_SetAction((task*)Test[i], &TestRing, ADV00_TEXLISTS[6], 0.0f, 1, 0);
			//CreateRotaryEmerald(playertwp[0]->pos.x, playertwp[0]->pos.y + 10.0f, playertwp[0]->pos.z, 10.0f, 800, Test[0], Test[1], Test[2], Test[3], Test[4], Test[5], Test[6]);
			//SetEffectRotaryEmerald(1, &ev_effect_list19, 0.5, 1.0, 1.0, 0.0, 0.0); //Used for the Colored Orbs
			//SetEffectRotaryEmerald(2, &ev_effect_list19, 0.5, 1.0, 0.0, 1.0, 0.0); //Used for the Colored Orbs
			//SetEffectRotaryEmerald(3, &ev_effect_list19, 0.5, 1.0, 1.0, 1.0, 1.0); //Used for the Colored Orbs
			//SetEffectRotaryEmerald(4, &ev_effect_list19, 0.5, 1.0, 1.0, 1.0, 0.0); //Used for the Colored Orbs
			//SetEffectRotaryEmerald(5, &ev_effect_list19, 0.5, 1.0, 1.0, 0.0, 1.0); //Used for the Colored Orbs
			//SetEffectRotaryEmerald(6, &ev_effect_list19, 0.5, 1.0, 0.0, 1.0, 1.0); //Used for the Colored Orbs
			//SetEffectRotaryEmerald(7, &ev_effect_list19, 0.5, 1.0, 0.0, 0.0, 1.0); //Used for the Colored Orbs
		}
		TestSpawned = 1;
		break;
	case 1:
		SplashRotaryEmerald(100.0f);
		TestSpawned = 2;
		break;
	case 2:
		deleteRotaryEmeraldTask();
		TestSpawned = 0;
		break;
	default:
		break;
	}
	strcpy_s(LastEffect, 128, "Test Ring");
}