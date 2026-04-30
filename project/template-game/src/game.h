#pragma once

#include <genesis.h>
#include "character.h"

#define MAX_CHARACTERS 10

enum GameState
{
    MENU,
    GAME,
    PAUSED,
    GAME_OVER
};

struct Game
{
    enum GameState state;

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

    game->state = MENU;
    game->isRunning = true;
    game->score = 0;
    game->level = 1;
    game->characterCount = 0;

    // Init Sprite
    SPR_init();
    JOY_init();
    VDP_init();
}

void StartGame(struct Game *game)
{
    if (game == NULL)
        return;

    game->state = GAME;
}
void PauseGame(struct Game *game)
{
    if (game == NULL)
        return;

    game->state = PAUSED;
}
void ResumeGame(struct Game *game)
{
    if (game == NULL)
        return;

    game->state = GAME;
}
void EndGame(struct Game *game)
{
    if (game == NULL)
        return;

    game->state = MENU;
}
void UpdateGame(struct Game *game)
{
    if (game->state == GAME)
    {
        // Update Characters
        for (int i = 0; i < game->characterCount; i++)
        {
            UpdateCharacter(&game->characters[i]);
        }
    }
}
void GameInputs(struct Game *game)
{
    if (JOY_readJoypad(JOY_1) & BUTTON_START)
    {
        if (game->state == MENU)
            StartGame(game);
        else if (game->state == GAME)
            PauseGame(game);
        else if (game->state == PAUSED)
            ResumeGame(game);
        else if (game->state == GAME_OVER)
            EndGame(game);
    }
}
void DrawGame(struct Game *game)
{
    switch (game->state)
    {
    case MENU:
    {
        VDP_drawText("Menu", 0, 0);
        break;
    }
    case GAME:
    {
        VDP_drawText("Game", 0, 0);
        SPR_update();
        break;
    }
    case PAUSED:
    {
        VDP_drawText("Paused", 0, 0);
        break;
    }
    case GAME_OVER:
    {
        VDP_drawText("Game Over", 0, 0);
        break;
    }
    }

    SYS_doVBlankProcess();
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
