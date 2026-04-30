/**
 * Hello World Example
 * Created With Genesis-Code extension for Visual Studio Code
 * Use "Genesis Code: Compile" command to compile this program.
 **/
#include <genesis.h>
#include "resources.h"

/// ---------------------------------- GAME ----------------------------------
struct Game
{
    // Game state variables
    bool isRunning;
    int score;
    int level;
};

void InitGame(struct Game *game)
{
    if (game == NULL)
        return;

    game->isRunning = true;
    game->score = 0;
    game->level = 1;

    JOY_init();

    // VDP_init();
    VDP_drawText("Hello Sega!!", 0, 0);
}

void UpdateGame(struct Game *game)
{
}

/// ---------------------------------- JOYPPAD ----------------------------------
u16 joypad1State = 0;
#define RIGHT (joypad1State & BUTTON_RIGHT)
#define LEFT (joypad1State & BUTTON_LEFT)
#define DOWN (joypad1State & BUTTON_DOWN)
#define UP (joypad1State & BUTTON_UP)
#define A (joypad1State & BUTTON_A)
#define B (joypad1State & BUTTON_B)
#define C (joypad1State & BUTTON_C)
#define START (joypad1State & BUTTON_START)

/// ---------------------------------- CHARACTER ----------------------------------
struct Character
{
    // Mouvement
    int x;
    int y;
    int speed;

    // Sprite
    Sprite *sprite;
};

void InitCharacter(struct Character *character, int startX, int startY, int speed, const SpriteDefinition *spriteDefinition)
{
    if (character == NULL)
        return;

    character->x = startX;
    character->y = startY;
    character->speed = speed;

    // Init Sprite
    SPR_init();

    PAL_setPalette(PAL2, spriteDefinition->palette->data, DMA);
    character->sprite = SPR_addSprite(spriteDefinition, character->x, character->y, TILE_ATTR(PAL2, FALSE, FALSE, FALSE));
}
void DrawCharacter(struct Character *character)
{
    SPR_update();
}

// Sprite Animations
#define FACE 0
#define SIDE 1
#define BACK 2

void UpdateCharacter(struct Character *character)
{
    // Sprite Move
    SPR_setPosition(character->sprite, character->x, character->y);

    // Sprite Animation
    if (RIGHT)
    {
        SPR_setAutoAnimation(character->sprite, TRUE);
        SPR_setAnim(character->sprite, SIDE);
        SPR_setHFlip(character->sprite, TRUE);
    }
    else if (LEFT)
    {
        SPR_setAutoAnimation(character->sprite, TRUE);
        SPR_setAnim(character->sprite, SIDE);
        SPR_setHFlip(character->sprite, FALSE);
    }
    else if (DOWN)
    {
        SPR_setAutoAnimation(character->sprite, TRUE);
        SPR_setAnim(character->sprite, FACE);
        SPR_setHFlip(character->sprite, FALSE);
    }
    else if (UP)
    {
        SPR_setAutoAnimation(character->sprite, TRUE);
        SPR_setAnim(character->sprite, BACK);
        SPR_setHFlip(character->sprite, FALSE);
    }
    else
    {
        SPR_setAutoAnimation(character->sprite, FALSE);
        SPR_setFrame(character->sprite, 0);
    }
}
void HandleCharacterInput(struct Character *player)
{
    // Input handling
    joypad1State = JOY_readJoypad(JOY_1);

    // Directions
    player->x += (RIGHT) ? player->speed : 0;
    player->x -= (LEFT) ? player->speed : 0;
    player->y += (DOWN) ? player->speed : 0;
    player->y -= (UP) ? player->speed : 0;
}

/// ---------------------------------- MAIN ----------------------------------
int main()
{
    // GAME
    struct Game game;
    InitGame(&game);

    // PLAYER 1
    struct Character player;
    InitCharacter(&player, 10, 10, 2, &friskSprite);

    // PLAYER 2
    // PNJ1
    // PNJ2

    while (game.isRunning)
    {
        // INPUT
        HandleCharacterInput(&player);

        // UPDATE
        UpdateGame(&game);
        UpdateCharacter(&player);

        // DRAW
        DrawCharacter(&player);

        SYS_doVBlankProcess();
    }
    return (0);
}
