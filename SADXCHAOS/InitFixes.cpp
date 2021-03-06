#include "pch.h"
#include <time.h>
#include <IniFile.hpp>
int EffectMax = 0;
bool DebugToScreen = false;
bool TeleportEnabled = true;
bool EnemysEnabled = true;
bool InvertEnabled = true;
bool RPauseEnabled = true;
bool PauseDisableEnabled = true;
bool GrabAbleObjectsEnabled = true;
bool GravityChangeEnabled = true;
bool RPhysicsEnabled = true;
bool EggViperHandyCapEanbled = true;
bool AllergicToRings = true;
bool UpsideDownCameraEnabled = true;
bool DrunkCameraEnabled = true;
bool SpinCameraEnabled = true;
bool RandomEmblemEnabled = true;
bool SideWaysCameraEnabled = true;
bool DetachCameraEnabled = true;
bool SoundDisableEnabled = true;
bool AndKnucklesEnabled = true;
bool RandomSongEnabled = true;
bool RandomVoiceEnabled = true;
DWORD Aequitas = (0x000000000761CFC0+0x0000000003B0E9E0+0x0000000003B0EFE0-0x000000000B12C1A0);
ObjectMaster* LoadSnowboardObject(LoadObj flags, char index, ObjectFuncPtr loadSub)
{
	return snowboard = LoadObject(flags, index, loadSub);
}
void __cdecl Snowboard_Delete_r(ObjectMaster* obj)
{
	njReleaseTexture((NJS_TEXLIST*)obj->Data1->LoopData);
	if (obj == snowboard)
		snowboard = nullptr;
}
void OverRideBigRockTex()
{
	njSetTexture(&OBJ_ICECAP_TEXLIST);
}
void LoadFETexObj()
{
	njSetTexture(&OBJ_FINALEGG_TEXLIST);
}
void LoadSDTexObj()
{
	njSetTexture(&OBJ_SKYDECK_TEXLIST);
}
void OverRideEmeraldShardObj()
{
	njSetTexture(&OBJ_RUIN_TEXLIST);
}
void OverRideTPBarrelObj()
{
	njSetTexture(&OBJ_TWINKLE_TEXLIST);
}
void Init_Fixes(const char* path, const HelperFunctions& helperFunctions)
{
	const IniFile* config = new IniFile(std::string(path) + "\\config.ini");
	EffectMax = config->getInt("Timer", "EffectMax", 180);
	DebugToScreen = config->getBool("Debug", "PrintToScreen", false);
	TeleportEnabled = config->getBool("General", "TeleportEnabled", true);
	EnemysEnabled = config->getBool("General", "EnemysEnabled", true);
	InvertEnabled = config->getBool("General", "InvertEnabled", true);
	RPauseEnabled = config->getBool("General", "PauseEnabled", true);
	PauseDisableEnabled = config->getBool("General", "PauseDisableEnabled", true);
	GrabAbleObjectsEnabled = config->getBool("General", "GrabAbleObjectsEnabled", true);
	GravityChangeEnabled = config->getBool("General", "GravityChangeEnabled", true);
	RPhysicsEnabled = config->getBool("General", "RPhysicsEnabled", true);
	AllergicToRings = config->getBool("General", "AllergicToRings", true);
	EggViperHandyCapEanbled = config->getBool("General", "EggViperHandyCap", true);
	RandomEmblemEnabled = config->getBool("General", "RandomEmblem", true);
	UpsideDownCameraEnabled = config->getBool("Camera", "UpsideDownCameraEnabled", true);
	DrunkCameraEnabled = config->getBool("Camera", "DrunkCameraEnabled", true);
	SpinCameraEnabled = config->getBool("Camera", "SpinCameraEnabled", true);
	SideWaysCameraEnabled = config->getBool("Camera", "SideWaysCameraEnabled", true);
	DetachCameraEnabled = config->getBool("Camera", "DetachCameraEnabled", true);
	SoundDisableEnabled = config->getBool("Sound", "SoundDisableEnabled", true);
	AndKnucklesEnabled = config->getBool("Sound", "AndKnucklesEnabled", true);
	RandomSongEnabled = config->getBool("Sound", "RandomSongEnabled", true);
	RandomVoiceEnabled = config->getBool("Sound", "RandomVoiceEnabled", true);
	delete config;
	InitializeRandomCoordinates();
	init_CartStuff(); //temp.walker need to test 3/26/2022 //sora credit
	WriteCall((void*)0x4E9423, LoadSnowboardObject);//fix for snowboard texture
	WriteCall((void*)0x4E967E, LoadSnowboardObject);//fix for snowboard texture
	WriteCall((void*)0x4E9698, LoadSnowboardObject);//fix for snowboard texture
	WriteCall((void*)0x597B34, LoadSnowboardObject);//fix for snowboard texture
	WriteCall((void*)0x597B46, LoadSnowboardObject);//fix for snowboard texture
	WriteCall((void*)0x4EDD17, OverRideBigRockTex); //fix for Big Ice Cap Rock Texture
	WriteCall((void*)0x5B7581, LoadFETexObj);//fix for Fan Texture
	WriteCall((void*)0x5BD65B, LoadFETexObj);//fix for Conveyor Texture
	WriteCall((void*)0x5BD271, LoadFETexObj);//fix for Conveyor Stop Texture
	WriteCall((void*)0x5F1A52, LoadSDTexObj);//fix for AirCraft Texture
	WriteCall((void*)0x5F1A78, LoadSDTexObj);//fix for AirCraft Texture
	WriteCall((void*)0x6F4BD5, OverRideEmeraldShardObj);//attempt to fix EmeraldShard Texture
	WriteCall((void*)0x6F4D81, OverRideEmeraldShardObj);//attempt to fix EmeraldShard Texture
	WriteCall((void*)0x6F4EE0, OverRideEmeraldShardObj);//attempt to fix EmeraldShard Texture
	WriteCall((void*)0x624047, OverRideTPBarrelObj);//fix for Twinkle Park Barrel
	WriteCall((void*)0x623CD1, OverRideTPBarrelObj);//fix for Twinkle Park Barrel
	WriteCall((void*)0x623D88, OverRideTPBarrelObj);//fix for Twinkle Park Barrel
	WriteData<1>((int*)0x624150, 0x25);//TwinklePark Barrel Timer Hack
	WriteData<1>((int*)0x624151, 0x00);//TwinklePark Barrel Timer Hack
	WriteJump(Snowboard_Delete, Snowboard_Delete_r);//fix for snowboard texture delete
	WriteData((char*)0x4EE7BB, (char)4);//Big ice rock pickup ability
	WriteData((int*)0x17D0A2C, (int)0xC7C35000);//Stops the amy key block from exploding 
	WriteData((int*)0x17D0A38, (int)0xC7C35000);//Stops the amy key block from exploding
	WriteData((int*)0x17D0A44, (int)0xC7C35000);//Stops the amy key block from exploding
	WriteData((int*)0x17D0A50, (int)0xC7C35000);//Stops the amy key block from exploding
	WriteData<5>((int*)0x4B4924, 0x90);//EmblemCollected_Load ControlDisable Nop
	WriteData<5>((int*)0x4B46C5, 0x90);//EmblemCollected_Main ControlDisable Nop
	WriteData<5>((int*)0x4B4924, 0x90);//InitGGMessage CameraSetEventCameraFunc Nop
	WriteData((int*)0x80F060, (int)0x47C35000);//FinalEgg Fan Set Accend Height Max Bypass //Temp.walker need to test (3/26/2022)
	//WriteData<1>((int*)0x4F6D60, 0xC3); //EC ACT 0 Stuff from sora for testing
	//WriteData<1>((int*)0x44AE80, 0xC3); //EC ACT 0 Stuff from sora for testing
	srand((unsigned)time(nullptr));
}