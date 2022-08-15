#include "platform.h"
#include "init.h"
#include "res/smpte_colour_bars.h"

#include <stdio.h>

int main(void)
{
    // Initialise parts of NDS we need
    init();

    // Initialise console for printing text
    PrintConsole* defConsole = consoleGetDefault();
    PrintConsole* console = consoleInit(NULL,
                                        0,
                                        BgType_Text4bpp,
                                        BgSize_T_256x256,
                                        defConsole->mapBase,
                                        defConsole->gfxBase,
                                        false,
                                        true);

    // Initialise background for displaying test patterns
    int PATTERN_BGID = bgInit(3, BgType_Bmp16, BgSize_B16_256x256, 0, 0);

    // Copy bitmap to video memory
    dmaCopy((const void*)smpte_colour_barsBitmap,
            bgGetGfxPtr(PATTERN_BGID),
            smpte_colour_barsBitmapLen);

    iprintf("Copied %d bytes from 0x%x to 0x%x\n",
            smpte_colour_barsBitmapLen,
            smpte_colour_barsBitmap,
            bgGetGfxPtr(PATTERN_BGID));

    while (true)
    {
        swiWaitForVBlank(); // Frame has been displayed, we can draw again :)

        scanKeys();
        if (keysDown() & KEY_START) break;
    }

    return 0;
}