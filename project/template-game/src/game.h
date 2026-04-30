#pragma once

#include <genesis.h>
#include "character.h"

#define MAX_CHARACTERS 10

struct Game
{
    // Game state variables
    bool isRunning;
    int score;
    int level;

    // list of characters
    struct Character characters[MAX_CHARACTERS];
    int characterCount;
};

void InitGame(struct Game *game)
{
    if (game == NULL)
        return;

    game->isRunning = true;
    game->score = 0;
    game->level = 1;
    game->characterCount = 0;

    // Init Sprite
    SPR_init();

    JOY_init();

    VDP_init();
    VDP_drawText("Hello Sega!!", 0, 0);
}

void AddCharacter(struct Game *game, struct Character *character)
{
    if (game == NULL || character == NULL || game->characterCount >= MAX_CHARACTERS)
        return;

    game->characters[game->characterCount] = *character;
    game->characterCount++;
}

void RemoveCharacter(struct Game *game, int index)
{
    if (game == NULL || index < 0 || index >= game->characterCount)
        return;

    for (int i = index; i < game->characterCount - 1; i++)
    {
        game->characters[i] = game->characters[i + 1];
    }
    game->characterCount--;
}

void UpdateGame(struct Game *game)
{
    // Update Characters
    for (int i = 0; i < game->characterCount; i++)
    {
        UpdateCharacter(&game->characters[i]);
    }
}

void DrawGame(struct Game *game)
{
    // Draw sprites
    SPR_update();

    SYS_doVBlankProcess();
}
