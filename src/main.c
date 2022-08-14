#include "platform.h"
#include "init.h"
#include "res/smpte_colour_bars.h"

#include <stdio.h>

int main(void)
{
    // Initialise parts of NDS we need
    init();

    // Initialise console for printing text
    PrintConsole console;
    consoleInit(&console, 0, BgType_Text4bpp, BgSize_T_256x256, 0, 0, false, true);

    // Initialise background for displaying test patterns
    int bg2_id = bgInit(2, BgType_Bmp16, BgSize_B16_256x256, 0, 0);

    dmaCopy((const void*)smpte_colour_barsBitmap, bgGetGfxPtr(bg2_id), 256*256);

    while (true)
    {
        swiWaitForVBlank(); // Frame has been displayed, we can draw again :)

        iprintf("Hello, World!\n");

        scanKeys();
        if (keysDown() & KEY_START) break;
    }

    return 0;
}