#include "init.h"

bool init(void)
{
    init_video();
    return true;
}

bool init_video(void)
{
    powerOn(POWER_LCD | POWER_2D_A);

    vramSetMainBanks(VRAM_A_MAIN_BG_0x06000000,
                    VRAM_B_MAIN_BG_0x06020000,
                    VRAM_C_SUB_BG_0x06200000,
                    VRAM_D_LCD);

    videoSetMode(MODE_5_2D | DISPLAY_BG2_ACTIVE);

    videoSetMode(MODE_5_2D | DISPLAY_BG3_ACTIVE);
    
    return true;
}