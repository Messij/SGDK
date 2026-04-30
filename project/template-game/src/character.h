#include <genesis.h>

/// ---------------------------------- CHARACTER ----------------------------------
struct Character
{
    // Mouvement
    int x;
    int y;
    int speed;
    int orientation;
    bool isMoving;

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

#define FACE 0
#define DOWN 0
#define SIDE 1
#define LEFT 2
#define RIGHT 1
#define BACK 2
#define UP 3

void UpdateCharacter(struct Character *character)
{
    // Control
    if (character->control >= JOY_1)
        HandlePlayerInput(character);
    // Control AI

    // Move
    SPR_setPosition(character->sprite, character->x, character->y);

    // Animation
    AnimateCharacter(character);
}

void AnimateCharacter(struct Character *character)
{ // Sprite Animation
    if (character->isMoving)
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
        player->x += player->speed;
        player->isMoving = true;
    }
    else if (JOY_readJoypad(player->control) & BUTTON_LEFT)
    {
        player->orientation = LEFT;
        player->x -= player->speed;
        player->isMoving = true;
    }
    else if (JOY_readJoypad(player->control) & BUTTON_DOWN)
    {
        player->orientation = DOWN;
        player->y += player->speed;
        player->isMoving = true;
    }
    else if (JOY_readJoypad(player->control) & BUTTON_UP)
    {
        player->orientation = UP;
        player->y -= player->speed;
        player->isMoving = true;
    }
    else
    {
        player->isMoving = false;
    }
    // Directions
    // player->x += (JOY_readJoypad(player->control) & BUTTON_RIGHT) ? player->speed : 0;
    // player->x -= (JOY_readJoypad(player->control) & BUTTON_LEFT) ? player->speed : 0;
    // player->y += (JOY_readJoypad(player->control) & BUTTON_DOWN) ? player->speed : 0;
    // player->y -= (JOY_readJoypad(player->control) & BUTTON_UP) ? player->speed : 0;
}
