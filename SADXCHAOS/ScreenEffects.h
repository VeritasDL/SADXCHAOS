#pragma once
//ScanLine
FunctionPointer(void, ___njColorBlendingMode, (int, int), 0x004030D0);
extern bool saveColOnce;
extern Angle originalAng0[1024];
extern Angle originalAng1[1024];
extern Angle originalAng2[1024];
struct ScanLineWork
{
	NJS_COLOR line_col;
	int res;
};
void __cdecl deleteScanLine1();
void __cdecl createScanLine1(unsigned __int8 a, unsigned __int8 r, unsigned __int8 g, unsigned __int8 b, int res);
//BootEffect
struct BootWork
{
	unsigned __int8 backGroundAlpha;
	unsigned __int8 da;
	unsigned int wait_frame;
	unsigned int sstorm_frame;
	unsigned int poweron_frame;
	unsigned int adjust_frame;
	unsigned int noise_frame;
};
void __cdecl deleteBoot1();
void __cdecl createBoot1(int wait_frame, int sstorm_frame, int poweron_frame, int adjust_frame);
void RandomScanLine();
void RandomBoot();
void HAHA69();
void LigmaBoss(); 
void ExplodeMa();
void SpinMa();
void SaveColAng();
void RestoreColAng();