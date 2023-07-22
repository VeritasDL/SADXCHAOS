#include "pch.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <vector>
#include <IniFile.hpp>
using std::string;
//Changelog Is Now Located inside Of Change.Log
char oldRand = -1;
char* LastEffect = new char[128];
uint32_t Veritas;
ObjectMaster* snowboard;
extern "C"
{
	__declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions)
	{
		Init_Fixes(path, helperFunctions);
		init_FreeMovements();
		strcpy_s(LastEffect, 128, "Chaos Edition 2.2");
	}
	ChaosS ChaosArray[139]
	{
	{ RandomBumper1, nullptr, nullptr },
	{ RandomSman, nullptr, nullptr },
	{ RandomFlipper, nullptr, nullptr },
	{ RandomTarget, nullptr, nullptr },
	{ RandomUnidus, nullptr, nullptr },
	{ RandomSnake, nullptr, nullptr },
	{ RandomConveyorBelt, nullptr, nullptr },
	{ SlapMa, nullptr, nullptr },
	{ RandomSpring, nullptr, nullptr },
	{ RandomGravityWall, nullptr, nullptr },
	{ RandomSpeedPad, nullptr, nullptr },
	{ RandomEGacha, nullptr, nullptr },
	{ RandomAirCraft, nullptr, nullptr },
	{ RandomSpring, nullptr, nullptr },
	{ RandomCannonS2, nullptr, nullptr },
	{ RandomDroppedRings, nullptr, nullptr },
	{ RandomPolice, nullptr, nullptr },
	{ RandomLifePowerup, nullptr, nullptr },
	{ BigRock, nullptr, nullptr },
	{ RandomBurgerMan, nullptr, nullptr },
	{ RandomKnuxRingSpring, nullptr, nullptr },
	{ RandomPowerUP, nullptr, nullptr },
	{ RandomTank, nullptr, nullptr },
	{ RandomSpikeBall, nullptr, nullptr },
	{ RandomCannonS1, nullptr, nullptr },
	{ RandomSpinnerC, nullptr, nullptr },
	{ RandomBurgerMan, nullptr, nullptr },
	{ RandomSpring, nullptr, nullptr },
	{ RandomHat, nullptr, nullptr },
	{ RandomWaterPiller, nullptr, nullptr },
	{ RandomPowerUP, nullptr, nullptr },
	{ RandomSpikeBall, nullptr, nullptr },
	{ RandomAirCraft, nullptr, nullptr },
	{ RandomDtarget, nullptr, nullptr },
	{ RandomPopUpTarget, nullptr, nullptr },
	{ RandomSpeedPad, nullptr, nullptr },
	{ RandomEmblem, nullptr, nullptr },
	{ RandomSpinnerB, nullptr, nullptr },
	{ RandomGravityWall, nullptr, nullptr },
	{ RandomAmebot, nullptr, nullptr },
	{ RandomLeon, nullptr, nullptr },
	{ RandomConveyorBelt, nullptr, nullptr },
	{ RandomCheckPoint, nullptr, nullptr },
	{ RandomKeyBlock, nullptr, nullptr },
	{ RandomSpinnerA, nullptr, nullptr },
	{ RandomFireBreath, nullptr, nullptr },
	{ RandomBurgerMan, nullptr, nullptr },
	{ RandomKeyBlock, nullptr, nullptr },
	{ RandomSpikeBall, nullptr, nullptr },
	{ BigRock, nullptr, nullptr },
	{ RandomBuyon, nullptr, nullptr },
	{ RandomCard, nullptr, nullptr },
	{ RandomPowerUP, nullptr, nullptr },
	{ RandomFireBreath, nullptr, nullptr },
	{ RandomFruit, nullptr, nullptr },
	{ RandomRobo, nullptr, nullptr },
	{ RandomSling, nullptr, nullptr },
	{ RandomBarrel, nullptr, nullptr },
	{ RandomFountain, nullptr, nullptr },
	{ RandomFan, nullptr, nullptr },
	{ nullptr, RandomVSpeed, nullptr },
	{ nullptr, RandomKillMomentum, nullptr },
	{ nullptr, RandomHSpeed, nullptr },
	{ nullptr, RandomVSpeed, nullptr },
	{ nullptr, RandomHSpeed, nullptr },
	{ nullptr, FastAccel, nullptr },
	{ nullptr, nullptr, SplashMa },
	{ nullptr, nullptr, DrunkCamera },
	{ nullptr, nullptr, RandomHurt },
	{ nullptr, nullptr, RandomPhysics },
	{ nullptr, nullptr, Tornado },
	{ nullptr, nullptr, RandomChaoo },
	{ nullptr, nullptr, IncreaseCutsceneSkipTime },
	{ nullptr, nullptr, RandomControlDisable },
	{ nullptr, nullptr, AndKnuckles },
	{ nullptr, nullptr, RandomTimeOfDay },
	{ nullptr, nullptr, RandomRotate },
	{ nullptr, nullptr, RemovePowerUp },
	{ nullptr, nullptr, RandomXGravity },
	{ nullptr, nullptr, RandomPause },
	{ nullptr, nullptr, Nos0und_ForYou },
	{ nullptr, nullptr, LigmaBoss },
	{ nullptr, nullptr, InputInvert },
	{ nullptr, nullptr, RemovePowerUp },
	{ nullptr, nullptr, SwapCamera },
	{ nullptr, nullptr, RandomTimeOfDay },
	{ nullptr, nullptr, RandomSwapMusic },
	{ nullptr, nullptr, RandomControlDisable },
	{ nullptr, nullptr, RingAllergy },
	{ nullptr, nullptr, RandomZGravity },
	{ nullptr, nullptr, RandomMagneticBarrier },
	{ nullptr, nullptr, RandomZGravity },
	{ nullptr, nullptr, RandomNoClip },
	{ nullptr, nullptr, BurgerManSpin },
	{ nullptr, nullptr, Set_Sonic_Ice },
	{ nullptr, nullptr, RandomTimeOfDay },
	{ nullptr, nullptr, RandomCart },
	{ nullptr, nullptr, RandomScanLine },
	{ nullptr, nullptr, RandomTeleport },
	{ nullptr, nullptr, RandomXGravity },
	{ nullptr, nullptr, SwapCamera },
	{ nullptr, nullptr, RingAllergy },
	{ nullptr, nullptr, RandomControlDisable },
	{ nullptr, nullptr, SideWaysCamera },
	{ nullptr, nullptr, RandomCollisionSize },
	{ nullptr, nullptr, RandomNoClip },
	{ nullptr, nullptr, SwapCamera },
	{ nullptr, nullptr, ChaosPlayVoice_rng },
	{ nullptr, nullptr, RandomTikalHint },
	{ nullptr, nullptr, NoGravity },
	{ nullptr, nullptr, RandomBoot },
	{ nullptr, nullptr, Set_Sonic_Ice },
	{ nullptr, nullptr, NoGravity },
	{ nullptr, nullptr, RandomNoClip },
	{ nullptr, nullptr, TornadoMa },
	{ nullptr, nullptr, DisablePausee },
	{ nullptr, nullptr, RandomYGravity },
	{ nullptr, nullptr, UncoupleCamera },
	{ nullptr, nullptr, ExplodeMa },
	{ nullptr, nullptr, RandomPause },
	{ nullptr, nullptr, HAHA69 },
	{ nullptr, nullptr, BurgerManSpin },
	{ nullptr, nullptr, IncreaseCutsceneSkipTime },
	{ nullptr, nullptr, RandomTimeOfDay },
	{ nullptr, nullptr, RandomBarrier },
	{ nullptr, nullptr, RandomTikalHint },
	{ nullptr, nullptr, SwapCamera },
	{ nullptr, nullptr, RandomYGravity },
	{ nullptr, nullptr, SpinCamera },
	{ nullptr, nullptr, RandomTimeOfDay },
	{ nullptr, nullptr, RandomCollisionSize },
	{ nullptr, nullptr, RandomHurt },
	{ nullptr, nullptr, FlipCamera },
	{ nullptr, nullptr, RandomDPadDownCheck },
	{ nullptr, nullptr, IncreaseCutsceneSkipTime },
	{ nullptr, nullptr, RandomInvincibility },
	{ nullptr, nullptr, RandomDebug },
	{ nullptr, nullptr, DrunkCamera },
	{ nullptr, nullptr, RandomSnowboard },
	};
	size_t ChaosSize = LengthOfArray(ChaosArray);
	__declspec(dllexport) void __cdecl OnFrame()
	{
		// Executed every running frame of SADX
		if (GameState != 15 && GameState != 16 && TextLoaded)
		{
			ResetTextureBools();
		}
		if (GameState != 15 && GameState != 16)
		{
			RestoreMain();
		}
		if (!playerpwp[0] || GameState != 15 || CurrentLevel == LevelIDs_SkyChase1 || CurrentLevel == LevelIDs_SkyChase2 || CurrentLevel >= LevelIDs_SSGarden)
			return;
		ChaosTimer();
		CheckAllEffectsTimer();
		DebugPrintOutCheck();
	}
	__declspec(dllexport) void __cdecl OnControl()
	{
		//Executed when the game processes input
		if (Controllers[0].PressedButtons & Buttons_Y) //Debug Testing
		{
			//pinball cards, ladder/hanging bars lol
		}
	}
	__declspec(dllexport) ModInfo SADXModInfo = { ModLoaderVer }; // This is needed for the Mod Loader to recognize the DLL.
}