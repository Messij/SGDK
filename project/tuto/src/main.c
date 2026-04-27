#include <genesis.h>
#include "resources.h"

int main()
{
    // Draw text
    VDP_drawText("Hello Sega!!", 0, 0);

    // Draw image
    PAL_setPalette(PAL1, moon.palette->data, CPU);
    VDP_drawImageEx(BG_A, &moon, TILE_ATTR_FULL(PAL1, 0, 0, 0, 1), 12, 12, 0, CPU);

    while (1)
    {
        SYS_doVBlankProcess();
    }
    return (0);
}
