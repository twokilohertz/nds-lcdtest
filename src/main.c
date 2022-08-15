#include "platform.h"
#include "init.h"
#include "patterns.h"

#include <stdio.h>

// Global state

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

    iprintf("Press A to cycle test patterns\nPress X to swap screens\nPress START to exit.");

    cycle_pattern(PATTERN_BGID); // Display first pattern (pattern 0 in patterns.c)

    while (true)
    {
        swiWaitForVBlank(); // Frame has been displayed, we can draw again :)

        scanKeys();
        if (keysDown() & KEY_START) break;
        if (keysDown() & KEY_X) swap_screens();
        if (keysDown() & KEY_A) cycle_pattern(PATTERN_BGID);
    }

    return 0;
}