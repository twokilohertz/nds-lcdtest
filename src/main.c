#include "platform.h"
#include "init.h"

#include <stdio.h>

int main(void)
{
    init();

    while (true)
    {
        printf("hello");
    }

    return 0;
}