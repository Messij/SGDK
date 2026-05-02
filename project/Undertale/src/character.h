#ifndef CHARACTER_H
#define CHARACTER_H

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

void InitCharacter(struct Character *character, int startX, int startY, int speed, const SpriteDefinition *spriteDefinition, u16 palette, int control);
void AnimateCharacter(struct Character *character);
void HandlePlayerInput(struct Character *player);
void HandleAIInput(struct Character *character);
void MoveCharacter(struct Character *character);
void UpdateCharacter(struct Character *character);
bool CharacterCollideWithOtherCharacter(struct Character *character, struct Character *other);
void DestroyCharacter(struct Character *character);

#endif