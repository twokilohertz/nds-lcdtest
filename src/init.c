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

    // Main engine is bound to the top screen
    lcdMainOnTop();

    // Map VRAM banks
    vramSetBankA(VRAM_A_MAIN_BG); // Bank A, main engine
    vramSetBankC(VRAM_C_SUB_BG); // Bank C, sub engine

    // Zero out memory
    memset(VRAM_A, 0, 128*1024);
    memset(VRAM_C, 0, 128*1024);
    
    /*

    Potential race condition with using dmaFill for this.
    Seems to zero out memory after the bitmap has been written to it.

    dmaFillWords(0, VRAM_A, 128*1024);
    dmaFillWords(0, VRAM_C, 128*1024);
    */

    // Set video modes
    videoSetMode(MODE_5_2D | DISPLAY_BG3_ACTIVE);
    videoSetModeSub(MODE_0_2D | DISPLAY_BG0_ACTIVE);
    
    return true;
}