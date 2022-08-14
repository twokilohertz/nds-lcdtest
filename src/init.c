#include "init.h"

bool init(void)
{
    init_video();
    return true;
}

bool init_video(void)
{
    // Power on the LCDs and 2D graphic core(s)
    powerOn(POWER_LCD | POWER_ALL_2D);

    // Map VRAM banks
    vramSetBankA(VRAM_A_MAIN_BG_0x06040000); // Bank A, main engine, background 2
    vramSetBankC(VRAM_C_SUB_BG_0x06200000); // Bank C, sub engine, background 0

    // Set video modes
    videoSetMode(MODE_5_2D | DISPLAY_BG2_ACTIVE);
    videoSetModeSub(MODE_0_2D | DISPLAY_BG0_ACTIVE);
    
    return true;
}