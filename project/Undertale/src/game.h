#pragma once

#include <genesis.h>
#include "character.h"
#include "variable.h"

#define ALL_CHARACTERS                                   \
    struct Character *character = &game->characters[0];  \
    character < &game->characters[game->characterCount]; \
    character++
#define ALL_PLAYERS                               \
    struct Character *player = &game->players[0]; \
    player < &game->players[game->playerCount];   \
    player++

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

    struct Character players[MAX_PLAYERS];
    int playerCount;

    // list of characters
    struct Character characters[MAX_CHARACTERS];
    int characterCount;
};
void InitGame(struct Game *game)
{
    if (game == NULL)
        return;

    game->state = GAME;
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
void RemoveCharacterFromGame(struct Game *game, int index)
{
    if (game == NULL || index < 0 || index >= game->characterCount)
        return;

    // free(&game->characters[index]);

    for (int i = index; i < game->characterCount - 1; i++)
    {
        game->characters[i] = game->characters[i + 1];
    }
    game->characterCount--;
}
void UpdateGame(struct Game *game)
{
    if (game->state == GAME)
    {
        for (ALL_PLAYERS)
        {
            UpdateCharacter(player);
        }
        for (ALL_CHARACTERS)
        {
            for (ALL_PLAYERS)
            {
                if (CharacterCollideWithOtherCharacter(character, player))
                {
                    DestroyCharacter(character);
                    RemoveCharacterFromGame(game, character - game->characters);
                    break;
                }
            }
        }

        GameInputs(game);
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
void AddCharacterToGame(struct Game *game, struct Character *character)
{
    if (game == NULL || character == NULL)
        return;

    if (character->control == AI && game->characterCount < MAX_CHARACTERS)
    {
        game->characters[game->characterCount] = *character;
        game->characterCount++;
    }
    else if (character->control != AI && game->playerCount < MAX_PLAYERS)
    {
        game->players[game->playerCount] = *character;
        game->playerCount++;
    }
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
