#pragma once
#include "SADXStructs.h"
#include "pch.h"
extern int EffectMax;
extern DWORD Aequitas;
extern bool DebugToScreen;
extern bool TeleportEnabled;
extern bool EnemysEnabled;
extern bool InvertEnabled;
extern bool RPauseEnabled;
extern bool PauseDisableEnabled;
extern bool GrabAbleObjectsEnabled;
extern bool GravityChangeEnabled;
extern bool RPhysicsEnabled;
extern bool EggViperHandyCapEanbled;
extern bool RandomEmblemEnabled;
extern bool SideWaysCameraEnabled;
extern bool SoundDisableEnabled;
extern bool DetachCameraEnabled;
extern bool AndKnucklesEnabled;
extern bool RandomSongEnabled;
extern bool RandomVoiceEnabled;
void Init_Fixes(const char* path, const HelperFunctions& helperFunctions);