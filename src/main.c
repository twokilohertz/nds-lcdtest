#include "platform.h"
#include "init.h"

#include <stdio.h>

int main(void)
{
    // Initialise parts of NDS we need
    init();

    // Initialise background for displaying test patterns
    int bg_id = bgInit(0, BgType_Bmp16, BgSize_B16_256x256, 0, 0);

    // todo: copy to vram, display on screen

    while (true)
    {
        swiWaitForVBlank();
        
    }

    return 0;
}