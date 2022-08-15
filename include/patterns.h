#ifndef PATTERNS_H
#define PATTERNS_H

#include "platform.h"

typedef struct Pattern
{
    const void* location;
    int         size;
} pattern;

void cycle_pattern(int background_id);
void swap_screens(void);

#endif