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

// Animations player 1
#define STATIC 0
#define IDLE 1
#define WALK 2
#define COMBO 3

// Animations player 2
#define STATIC2 0
#define IDLE2 1
#define WALK2 2
#define COMBO2 3

// Control
Sprite *playerSprite;
int player_x = 0;
int player_y = 0;
int player_speed = 2;

// Control
Sprite *player2Sprite;
int player2_x = 0;
int player2_y = 0;
int player2_speed = 4;

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

u16 joypad2State = 0;
#define RIGHT2 (joypad2State & BUTTON_RIGHT)
#define LEFT2 (joypad2State & BUTTON_LEFT)
#define DOWN2 (joypad2State & BUTTON_DOWN)
#define UP2 (joypad2State & BUTTON_UP)
#define A2 (joypad2State & BUTTON_A)
#define B2 (joypad2State & BUTTON_B)
#define C2 (joypad2State & BUTTON_C)
#define START2 (joypad2State & BUTTON_START)

static void HandleInput()
{
    // Directions
    player_x += (RIGHT) ? player_speed : 0;
    player_x -= (LEFT) ? player_speed : 0;
    player_y += (DOWN) ? player_speed : 0;
    player_y -= (UP) ? player_speed : 0;

    // Directions
    player2_x += (RIGHT2) ? player2_speed : 0;
    player2_x -= (LEFT2) ? player2_speed : 0;
    player2_y += (DOWN2) ? player2_speed : 0;
    player2_y -= (UP2) ? player2_speed : 0;
}

static void UpdatePlayerSpritePosition()
{
    SPR_setPosition(playerSprite, player_x, player_y);
    SPR_setPosition(player2Sprite, player2_x, player2_y);
}

static void UpdatePlayerSpriteAnimation()
{
    if (RIGHT || LEFT || DOWN || UP)
        SPR_setAnim(playerSprite, WALK);
    else
        SPR_setAnim(playerSprite, IDLE);

    if (RIGHT2 || LEFT2 || DOWN2 || UP2)
        SPR_setAnim(player2Sprite, WALK2);
    else
        SPR_setAnim(player2Sprite, IDLE2);
}

static void UpdatePlayerSpriteFlip()
{
    if (RIGHT)
        SPR_setHFlip(playerSprite, TRUE);
    else if (LEFT)
        SPR_setHFlip(playerSprite, FALSE);

    if (RIGHT2)
        SPR_setHFlip(player2Sprite, FALSE);
    else if (LEFT2)
        SPR_setHFlip(player2Sprite, TRUE);
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
        PAL_setPalette(PAL3, sonicSprite.palette->data, DMA);

        playerSprite = SPR_addSprite(&axelSprite, player_x, player_y, TILE_ATTR(PAL2, FALSE, FALSE, FALSE));
        player2Sprite = SPR_addSprite(&sonicSprite, player2_x, player2_y, TILE_ATTR(PAL3, FALSE, FALSE, FALSE));

        SPR_setAnim(playerSprite, IDLE);
        SPR_setAnim(player2Sprite, IDLE);
    }
    if (controlPlayer)
    {
        JOY_init();
        JOY_setEventHandler(JoypadEvents);
    }

    while (runGame)
    {
        // JOY_update();
        joypad1State = JOY_readJoypad(JOY_1);
        joypad2State = JOY_readJoypad(JOY_2);

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
