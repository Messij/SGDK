#include <genesis.h>
#include "resources.h"

// Control
Sprite *playerSprite;
int player_x = 50;
int player_y = 50;
int player_speed = 2;

u16 joypad1State = 0;
#define RIGHT (joypad1State & BUTTON_RIGHT)
#define LEFT (joypad1State & BUTTON_LEFT)
#define DOWN (joypad1State & BUTTON_DOWN)
#define UP (joypad1State & BUTTON_UP)
#define A (joypad1State & BUTTON_A)
#define B (joypad1State & BUTTON_B)
#define C (joypad1State & BUTTON_C)
#define START (joypad1State & BUTTON_START)

// salut

// Animations player 1
#define FACE 0
#define SIDE 1
#define BACK 2

int main()
{
    VDP_drawText("Hello Frisk !", 10, 1);

    // Draw
    SPR_init();
    PAL_setPalette(PAL2, friskSprite.palette->data, DMA);
    playerSprite = SPR_addSprite(&friskSprite, player_x, player_y, TILE_ATTR(PAL2, FALSE, FALSE, FALSE));

    // Input
    JOY_init();

    while (1)
    {
        joypad1State = JOY_readJoypad(JOY_1);

        // Directions
        player_x += (RIGHT) ? player_speed : 0;
        player_x -= (LEFT) ? player_speed : 0;
        player_y += (DOWN) ? player_speed : 0;
        player_y -= (UP) ? player_speed : 0;

        SPR_setPosition(playerSprite, player_x, player_y);

        if (RIGHT)
        {
            SPR_setAutoAnimation(playerSprite, TRUE);
            SPR_setAnim(playerSprite, SIDE);
            SPR_setHFlip(playerSprite, TRUE);
        }
        else if (LEFT)
        {
            SPR_setAutoAnimation(playerSprite, TRUE);
            SPR_setAnim(playerSprite, SIDE);
            SPR_setHFlip(playerSprite, FALSE);
        }
        else if (DOWN)
        {
            SPR_setAutoAnimation(playerSprite, TRUE);
            SPR_setAnim(playerSprite, FACE);
            SPR_setHFlip(playerSprite, FALSE);
        }
        else if (UP)
        {
            SPR_setAutoAnimation(playerSprite, TRUE);
            SPR_setAnim(playerSprite, BACK);
            SPR_setHFlip(playerSprite, FALSE);
        }
        else
        {
            SPR_setAutoAnimation(playerSprite, FALSE);
            SPR_setFrame(playerSprite, 0);
        }

        SPR_update();
        SYS_doVBlankProcess();
    }
    return (0);
}
