#pragma once

#include <genesis.h>
#include "variable.h"

#pragma region Constants
#define AI -1
#define FACE 0
#define SIDE 1
#define BACK 2
#define DOWN 0
#define LEFT 2
#define RIGHT 1
#define UP 3
#pragma endregion

struct Character
{
    // Mouvement
    int x;
    int y;
    int speed;
    int orientation;
    bool moves;
    // bool isMoving;

    // Sprite
    Sprite *sprite;

    // Control
    int control;
};
void InitCharacter(struct Character *character, int startX, int startY, int speed, const SpriteDefinition *spriteDefinition, int control)
{
    if (character == NULL)
        return;

    character->x = startX;
    character->y = startY;
    character->speed = speed;
    character->control = control;

    PAL_setPalette(PAL2, spriteDefinition->palette->data, DMA);
    character->sprite = SPR_addSprite(spriteDefinition, character->x, character->y, TILE_ATTR(PAL2, FALSE, FALSE, FALSE));
    SPR_setAutoAnimation(character->sprite, FALSE);
    SPR_setFrame(character->sprite, 0);
}
void AnimateCharacter(struct Character *character)
{
    if (character->moves)
    {
        if (character->orientation == RIGHT)
        {
            SPR_setAutoAnimation(character->sprite, TRUE);
            SPR_setAnim(character->sprite, SIDE);
            SPR_setHFlip(character->sprite, TRUE);
        }
        else if (character->orientation == LEFT)
        {
            SPR_setAutoAnimation(character->sprite, TRUE);
            SPR_setAnim(character->sprite, SIDE);
            SPR_setHFlip(character->sprite, FALSE);
        }
        else if (character->orientation == DOWN)
        {
            SPR_setAutoAnimation(character->sprite, TRUE);
            SPR_setAnim(character->sprite, FACE);
            SPR_setHFlip(character->sprite, FALSE);
        }
        else if (character->orientation == UP)
        {
            SPR_setAutoAnimation(character->sprite, TRUE);
            SPR_setAnim(character->sprite, BACK);
            SPR_setHFlip(character->sprite, FALSE);
        }
    }
    else
    {
        SPR_setAutoAnimation(character->sprite, FALSE);
        SPR_setFrame(character->sprite, 0);
    }
}
void HandlePlayerInput(struct Character *player)
{
    // Orientation
    if (JOY_readJoypad(player->control) & BUTTON_RIGHT)
    {
        player->orientation = RIGHT;
        player->moves = true;
    }
    else if (JOY_readJoypad(player->control) & BUTTON_LEFT)
    {
        player->orientation = LEFT;
        player->moves = true;
    }
    else if (JOY_readJoypad(player->control) & BUTTON_DOWN)
    {
        player->orientation = DOWN;
        player->moves = true;
    }
    else if (JOY_readJoypad(player->control) & BUTTON_UP)
    {
        player->orientation = UP;
        player->moves = true;
    }
    else
    {
        player->moves = false;
    }
    // Directions
    // player->x += (JOY_readJoypad(player->control) & BUTTON_RIGHT) ? player->speed : 0;
    // player->x -= (JOY_readJoypad(player->control) & BUTTON_LEFT) ? player->speed : 0;
    // player->y += (JOY_readJoypad(player->control) & BUTTON_DOWN) ? player->speed : 0;
    // player->y -= (JOY_readJoypad(player->control) & BUTTON_UP) ? player->speed : 0;
}
void HandleAIInput(struct Character *character)
{
    // AI Logic
    // decide to move or not
    if (random() % 600 == 0) // 5% chance to change movement state
    {
        character->moves = !character->moves; // Toggle movement state
    }

    // Random orientation change
    if (random() % 60 == 0) // Change direction every 60 frames
    {
        character->orientation = random() % 4; // Random orientation (0-3)
    }
    // Move in the current orientation
    // switch (character->orientation)
    // {
    // case RIGHT:
    // case LEFT:
    // case DOWN:
    // case UP:
    //     character->moves = true;
    //     break;
    // default:
    //     character->moves = false;
    //     break;
    // }
}
void MoveCharacter(struct Character *character)
{
    if (character->moves)
    {
        switch (character->orientation)
        {
        case RIGHT:
            if (character->x + character->sprite->definition->w + character->speed < SCREEN_WIDTH)
                character->x += character->speed;
            else
                character->moves = false;
            break;
        case LEFT:
            if (character->x - character->speed > 0)
                character->x -= character->speed;
            else
                character->moves = false;
            break;
        case DOWN:
            if (character->y + character->sprite->definition->h + character->speed < SCREEN_HEIGHT)
                character->y += character->speed;
            else
                character->moves = false;
            break;
        case UP:
            if (character->y - character->speed > 0)
                character->y -= character->speed;
            else
                character->moves = false;
            break;
        }
    }

    SPR_setPosition(character->sprite, character->x, character->y);
}
void UpdateCharacter(struct Character *character)
{
    // Control
    if (character->control >= JOY_1)
        HandlePlayerInput(character);
    else
        HandleAIInput(character);

    // Move
    MoveCharacter(character);

    // Animation
    AnimateCharacter(character);
}