#include <genesis.h>
#include "resources.h"

int hScrollOffset_Background = 0;
int hScrollOffset_Foreground = 0;
int hScrollOffsetSpeed = -1;

bool drawText = 0;
bool drawImage = 0;
bool drawBackgroundAndForground = 0;
bool drawSprite = 1;

bool runGame = 1;

int main()
{
    if (drawText)
    {
        VDP_drawText("Hello Sega !!", 0, 0);
    }

    if (drawImage)
    {
        PAL_setPalette(PAL1, moon.palette->data, CPU);
        VDP_drawImageEx(BG_A, &moon, TILE_ATTR_FULL(PAL1, 0, 0, 0, 1), 12, 12, 0, CPU);
    }

    if (drawBackgroundAndForground)
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

    if (drawSprite)
    {
        SPR_init();
        PAL_setPalette(PAL2, axelSprite.palette->data, DMA);
        Sprite *axel = SPR_addSprite(&axelSprite, 100, 50, TILE_ATTR(PAL2, FALSE, FALSE, FALSE));
    }

    while (runGame)
    {
        if (drawBackgroundAndForground)
        {
            VDP_setHorizontalScroll(BG_B, hScrollOffset_Background += hScrollOffsetSpeed);
            VDP_setHorizontalScroll(BG_A, hScrollOffset_Foreground += hScrollOffsetSpeed * 2);
        }

        if (drawSprite)
        {
            SPR_update();
        }

        SYS_doVBlankProcess();
    }
    return (0);
}
