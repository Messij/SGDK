#include <genesis.h>
#include "resources.h"

// scrolling
int hScrollOffset_Background = 0;
int hScrollOffset_Foreground = 0;
int hScrollOffsetSpeed = -1;

// Options
bool runGame = 1;
bool drawText = 1;
bool drawImage = 0;
bool drawBackgroundAndForground = 1;
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

// Attack
int attackTimer = 0;
int attackDuration = 56; // Duration of the attack animation in frames
bool isAttacking = FALSE;

u16 joypad1State = 0;
#define RIGHT (joypad1State & BUTTON_RIGHT)
#define LEFT (joypad1State & BUTTON_LEFT)
#define DOWN (joypad1State & BUTTON_DOWN)
#define UP (joypad1State & BUTTON_UP)
#define A (joypad1State & BUTTON_A)
#define B (joypad1State & BUTTON_B)
#define C (joypad1State & BUTTON_C)
#define START (joypad1State & BUTTON_START)

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
    else
        SPR_setAnim(playerSprite, IDLE);
}

static void UpdatePlayerSpriteFlip()
{
    if (RIGHT)
        SPR_setHFlip(playerSprite, TRUE);
    else if (LEFT)
        SPR_setHFlip(playerSprite, FALSE);
}

static void JoypadEvents(u16 joy, u16 changed, u16 state)
{
    if (changed & state & BUTTON_A && isAttacking == FALSE)
    {
        SPR_setAnim(playerSprite, COMBO);
        isAttacking = TRUE;
        attackTimer = 0; // Reset the attack timer when the attack starts
    }
}

int main()
{
    if (drawText)
    {
        VDP_drawText("Hello Sega !!", 0, 0);
        VDP_drawText(isAttacking ? "Attacking!" : "Not Attacking", 0, 1);
    }
    if (drawImage)
    {
        PAL_setPalette(PAL1, moon.palette->data, CPU);
        VDP_drawImageEx(BG_A, &moon, TILE_ATTR_FULL(PAL1, 0, 0, 0, 1), 12, 12, 0, CPU);
    }
    if (drawBackgroundAndForground)
    {
        const Image *bg = &bgStreet1;
        const Image *fg = &fgStreet1;
        u16 ind = TILE_USER_INDEX;

        // Background
        if (bg)
        {
            PAL_setPalette(PAL0, bg->palette->data, DMA);
            VDP_drawImageEx(BG_B, bg, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, ind), 0, 0, FALSE, TRUE);
            ind += bg->tileset->numTile;
        }

        // Foreground
        if (fg && 0)
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
        JOY_init();
        JOY_setEventHandler(JoypadEvents);
    }

    while (runGame)
    {
        JOY_update();
        joypad1State = JOY_readJoypad(JOY_1);

        if (drawText)
        {
            // Ajouter l'affichage de la valeur d'attackTimer
            char buffer[16]; // Buffer pour stocker la chaîne formatée
            sprintf(buffer, "Timer: %d", attackTimer);
            VDP_drawText(buffer, 0, 2); // Afficher à la ligne 2

            sprintf(buffer, "JOY:%04X", joypad1State);
            VDP_drawText(buffer, 0, 3); // Afficher la valeur brute du pad
        }
        if (drawBackgroundAndForground)
        {
            // VDP_setHorizontalScroll(BG_B, hScrollOffset_Background += hScrollOffsetSpeed);
            // VDP_setHorizontalScroll(BG_A, hScrollOffset_Foreground += hScrollOffsetSpeed * 2);
        }
        if (controlPlayer)
        {
            if (!isAttacking)
            {
                HandleInput();
                UpdatePlayerSpriteAnimation();
                UpdatePlayerSpritePosition();
                UpdatePlayerSpriteFlip();
            }
            else if (attackTimer < attackDuration)
                attackTimer++;
            else
                isAttacking = FALSE;
        }
        if (drawSprite)
        {
            SPR_update();
        }
        SYS_doVBlankProcess();
    }
    return (0);
}
