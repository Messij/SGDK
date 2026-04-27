#include <genesis.h>
#include "resources.h"

// scrolling
int hScrollOffset_Background = 0;
int hScrollOffset_Foreground = 0;
int hScrollOffsetSpeed = -1;

// Options
bool runGame = 1;
bool drawText = 0;
bool drawImage = 0;
bool drawBackgroundAndForground = 0;
bool drawSprite = 1;
bool controlPlayer = 1;

// Animations
#define STATIC 0
#define IDLE 1
#define WALK 2
#define COMBO 3

// Control
Sprite *playerSprite;
int player_x = 100;
int player_y = 50;
int player_speed = 2;

#define RIGHT JOY_readJoypad(JOY_1) & BUTTON_RIGHT
#define LEFT JOY_readJoypad(JOY_1) & BUTTON_LEFT
#define DOWN JOY_readJoypad(JOY_1) & BUTTON_DOWN
#define UP JOY_readJoypad(JOY_1) & BUTTON_UP
#define A (JOY_readJoypad(JOY_1) & BUTTON_A)
#define B JOY_readJoypad(JOY_1) & BUTTON_B
#define C JOY_readJoypad(JOY_1) & BUTTON_C
#define START JOY_readJoypad(JOY_1) & BUTTON_START

static void HandleInput()
{
    // Directions
    player_x += (RIGHT) ? player_speed : 0;
    player_x -= (LEFT) ? player_speed : 0;
    player_y += (DOWN) ? player_speed : 0;
    player_y -= (UP) ? player_speed : 0;
}

static void UpdatePlayerSpritePosition()
{
    SPR_setPosition(playerSprite, player_x, player_y);
}

static void UpdatePlayerSpriteAnimation()
{
    if (RIGHT || LEFT || DOWN || UP)
        SPR_setAnim(playerSprite, WALK);
    else if (!A)
        SPR_setAnim(playerSprite, IDLE);
}

static void UpdatePlayerSpriteFlip()
{
    if (RIGHT)
        SPR_setHFlip(playerSprite, TRUE);
    else if (LEFT)
        SPR_setHFlip(playerSprite, FALSE);
}

static void JoyEvents(u16 joy, u16 changed, u16 state)
{
    if (changed & state & BUTTON_A)
    {
        SPR_setAnim(playerSprite, COMBO);
    }
}

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
        playerSprite = SPR_addSprite(&axelSprite, player_x, player_y, TILE_ATTR(PAL2, FALSE, FALSE, FALSE));
        SPR_setAnim(playerSprite, IDLE);
    }
    if (controlPlayer)
    {
        JOY_setEventHandler(JoyEvents);
    }

    while (runGame)
    {
        if (drawBackgroundAndForground)
        {
            VDP_setHorizontalScroll(BG_B, hScrollOffset_Background += hScrollOffsetSpeed);
            VDP_setHorizontalScroll(BG_A, hScrollOffset_Foreground += hScrollOffsetSpeed * 2);
        }
        if (controlPlayer)
        {
            HandleInput();
            JOY_update();
            UpdatePlayerSpriteAnimation();
            UpdatePlayerSpritePosition();
            UpdatePlayerSpriteFlip();
        }
        if (drawSprite)
        {
            SPR_update();
        }

        SYS_doVBlankProcess();
    }
    return (0);
}
