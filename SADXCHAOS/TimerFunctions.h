#pragma once
#include "Chaos.h"
extern int Chaos_Timer;
extern int Debug_Timer;
extern int Pause_Timer;
extern int DPadDown_Timer;
extern int DisableControl_Timer;
extern int XGravity_Timer;
extern int YGravity_Timer;
extern int ZGravity_Timer;
extern int NoGravityTimer;
extern int InputInvert_Timer;
extern int NoClip_Timer;
extern int FastAccel_Timer;
extern int Camera_Timer;
extern int s0und__Timer;
extern int DisablePause_Timer;
extern int Animaltyperand;
extern int RingAllergy_Timer;
extern int AirCraftSpawerFollow_Timer;
extern int CameraFlip_Timer;
extern int CameraSpin_Timer;
extern int DrunkCamera_Timer;
extern int SnowboardTimer;
extern int CameraSpin_Val;
extern int DrunkCam;
extern int Direction;
extern int SideWaysCamera_Timer;
extern int BurgerSpin_Timer;
extern int Cart_Timer;
extern int WaterPiller_Timer;
extern int ScanLine_Timer;
extern int RandomBoot_Timer;
extern bool DebugEnabled;
void NoClipTimerCheck();
void InputInvertTimerCheck();
void CameraDeattchTimerCheck();
void XYZGravityTimerCheck();
void NoGravityTimerCheck();
void DisableControlTimerCheck();
void DpadDownOrDieTimerCheck();
void ForcePauseTimerCheck();
void SnowBoardTimerCheck();
void FastAccelTimerCheck();
void Nos0und__TimerCheck();
void RingAllergyTimerCheck();
void PauseDisableTimerCheck();
void CustomCameraEffectsTimersCheck();
void DebugTimerCheck();
void AirCraftSpawnerTimerCheck();
void CheckAllEffectsTimer();
void ChaosTimer();