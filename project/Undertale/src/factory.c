#include "factory.h"

struct Character *CreateCharacter(struct Game *game, int startX, int startY, int speed, const SpriteDefinition *spriteDefinition, u16 palette, int control)
{
    struct Character *character = (struct Character *)malloc(sizeof(struct Character));
    if (character == NULL)
        return NULL;

    InitCharacter(character, startX, startY, speed, spriteDefinition, palette, control);
    AddCharacterToGame(game, character);
    return character;
}