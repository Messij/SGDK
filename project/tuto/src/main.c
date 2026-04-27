#include <genesis.h>
#include "resources.h"

int hScrollOffset_Background = 0;
int hScrollOffset_Foreground = 0;
int hScrollOffsetSpeed = -1;

bool activeText = 1;
bool activeImage = 0;
bool activeBGFG = 0;

int main()
{
    // Draw text
    if (activeText)
    {
        VDP_drawText("Hello Sega !!", 0, 0);
    }

    // Draw image
    if (activeImage)
    {
        PAL_setPalette(PAL1, moon.palette->data, CPU);
        VDP_drawImageEx(BG_A, &moon, TILE_ATTR_FULL(PAL1, 0, 0, 0, 1), 12, 12, 0, CPU);
    }

    // Draw bakground and forground
    if (activeBGFG)
    {
        const Image *bg = &bgSonic1;
        const Image *fg = &fgSonic1;
        u16 ind = TILE_USER_INDEX;

        // Background
        if (bg)
        {
            PAL_setPalette(PAL0, bg->palette->data, DMA);
            VDP_drawImageEx(BG_B, bg, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, ind), 0, 0, FALSE, TRUE);
            ind += bg->tileset->numTile;
        }

        // Foreground
        if (fg)
        {
            PAL_setPalette(PAL1, fg->palette->data, DMA);
            VDP_drawImageEx(BG_A, fg, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, ind), 0, 0, FALSE, TRUE);
            ind += fg->tileset->numTile;
        }

        // Scroll background
        VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);
    }

    while (1)
    {
        // Scroll background
        if (activeBGFG)
        {
            VDP_setHorizontalScroll(BG_B, hScrollOffset_Background += hScrollOffsetSpeed);
            VDP_setHorizontalScroll(BG_A, hScrollOffset_Foreground += hScrollOffsetSpeed * 2);
        }

        SYS_doVBlankProcess();
    }
    return (0);
}
