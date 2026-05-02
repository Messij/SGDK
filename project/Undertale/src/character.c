#include "character.h"

void InitCharacter(struct Character *character, int startX, int startY, int speed, const SpriteDefinition *spriteDefinition, u16 palette, int control)
{
    if (character == NULL)
        return;

    character->x = startX;
    character->y = startY;
    character->speed = speed;
    character->control = control;

    PAL_setPalette(palette, spriteDefinition->palette->data, DMA);
    character->sprite = SPR_addSprite(spriteDefinition, character->x, character->y, TILE_ATTR(palette, FALSE, FALSE, FALSE));
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
        if (character->moves)
            SPR_setPosition(character->sprite, character->x, character->y);
    }
}
void UpdateCharacter(struct Character *character)
{
    // Control
    if (character->control == AI)
    {
        // HandleAIInput(character);
    }
    else
        HandlePlayerInput(character);
    // Move
    MoveCharacter(character);
    // Animation
    AnimateCharacter(character);
}
bool CharacterCollideWithOtherCharacter(struct Character *character, struct Character *other)
{
    // Collision logic
    if (
        character->x > other->x && character->x < other->x + other->sprite->definition->w && character->y > other->y && character->y < other->y + other->sprite->definition->h)
    {
        return true;
    }
    return false;
}
void DestroyCharacter(struct Character *character)
{
    if (character == NULL)
        return;

    SPR_releaseSprite(character->sprite);
    // free(character);
}

