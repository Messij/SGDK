#ifndef FACTORY_H
#define FACTORY_H

#include <genesis.h>
#include "character.h"
#include "resources.h"
#include "game.h"

struct Character *CreateCharacter(struct Game *game, int startX, int startY, int speed, const SpriteDefinition *spriteDefinition, u16 palette, int control);

#endif