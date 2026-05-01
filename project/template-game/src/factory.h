#pragma once

#include <genesis.h>
#include "character.h"
#include "resources.h"
#include "game.h"

struct Character *CreateCharacter(struct Game *game, int startX, int startY, int speed, const SpriteDefinition *spriteDefinition, int control)
{
    struct Character *character = (struct Character *)malloc(sizeof(struct Character));
    if (character == NULL)
        return NULL;

    InitCharacter(character, startX, startY, speed, spriteDefinition, control);
    AddCharacterToGame(game, character);
    return character;
}