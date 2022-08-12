#include "init.h"

bool init(void)
{
    init_video();
    return true;
}

bool init_video(void)
{
    powerOn(POWER_LCD | POWER_2D_A);

    vramSetBankA(VRAM_A_MAIN_BG_0x06000000);

    videoSetMode(MODE_5_2D | DISPLAY_BG0_ACTIVE);
    
    return true;
}