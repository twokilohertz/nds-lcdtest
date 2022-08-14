#include "init.h"

bool init(void)
{
    init_video();
    return true;
}

bool init_video(void)
{
    powerOn(POWER_LCD | POWER_ALL_2D);

    vramSetBankA(VRAM_A_MAIN_BG_0x06000000);
    vramSetBankC(VRAM_C_SUB_BG_0x06200000);

    videoSetMode(MODE_5_2D | DISPLAY_BG2_ACTIVE);
    videoSetModeSub(MODE_0_2D | DISPLAY_BG0_ACTIVE);
    
    return true;
}