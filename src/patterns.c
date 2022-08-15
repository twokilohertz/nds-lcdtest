#include "patterns.h"

#include "res/smpte_colour_bars.h"
#include "res/gradient.h"
#include "res/horizontal_lines.h"
#include "res/vertical_lines.h"

int current_pattern = -1;
pattern patterns[] =    {
                        {(const void*)smpte_colour_barsBitmap, smpte_colour_barsBitmapLen},
                        {(const void*)gradientBitmap, gradientBitmapLen},
                        {(const void*)horizontal_linesBitmap, horizontal_linesBitmapLen},
                        {(const void*)vertical_linesBitmap, vertical_linesBitmapLen}
                        };

void cycle_pattern(int background_id)
{
    current_pattern++;
    if (current_pattern == sizeof(patterns)/sizeof(pattern))
        current_pattern = 0;

    dmaCopy(patterns[current_pattern].location,
            bgGetGfxPtr(background_id),
            patterns[current_pattern].size);

    return;
}

void swap_screens(void)
{
    lcdSwap();
    return;
}