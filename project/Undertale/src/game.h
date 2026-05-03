#ifndef GAME_H
#define GAME_H

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
    // State
    enum GameState state;
    bool changeState;
    bool isRunning;
    int score;
    int level;

    // List of player
    struct Character players[MAX_PLAYERS];
    int playerCount;

    // list of characters
    struct Character characters[MAX_CHARACTERS];
    int characterCount;
};
void InitGame(struct Game *game);
void StartGame(struct Game *game);
void PauseGame(struct Game *game);
void ResumeGame(struct Game *game);
void EndGame(struct Game *game);
void GameInputs(struct Game *game);
void RemoveCharacterFromGame(struct Game *game, int index);
void UpdateGame(struct Game *game);
void DrawGame(struct Game *game);
void AddCharacterToGame(struct Game *game, struct Character *character);
void SpawnEnemy(struct Game *game);
#endif