#include <genesis.h>
#include "game.h"
#include "resources.h"
#include "factory.h"
#include "character.h"

void InitGame(struct Game *game)
{
    if (game == NULL)
        return;

    // State
    game->state = MENU;
    game->changeState = false;
    game->isRunning = true;
    game->score = 0;
    game->level = 1;

    game->characterCount = 0;
    game->playerCount = 0;

    // Init Sprite
    SPR_init();
    JOY_init();
    VDP_init();
}
void StartGame(struct Game *game)
{
    if (game == NULL)
        return;

    setRandomSeed(getTick());
    SpawnEnemy(game);
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
    if (JOY_readJoypad(JOY_1) & BUTTON_START && !game->changeState)
    {
        game->changeState = true;
        // Start Game
        if (game->state == MENU)
            StartGame(game);
        // Pause Game
        else if (game->state == GAME)
            PauseGame(game);
        // End Game
        else if (game->state == PAUSED)
            ResumeGame(game);
    }
    else if (JOY_readJoypad(JOY_1) & BUTTON_START && game->changeState)
    {
        // wait for button release to change state again
    }
    else
    {
        game->changeState = false;
    }
}
void RemoveCharacterFromGame(struct Game *game, int index)
{
    if (game == NULL || index < 0 || index >= game->characterCount)
        return;

    // DestroyCharacter(&game->characters[index]);
    // SPR_releaseSprite(game->characters[index]->sprite);
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
            UpdateCharacter(player);

        for (ALL_CHARACTERS)
            for (ALL_PLAYERS)
                if (CharacterCollideWithOtherCharacter(character, player))
                {
                    // DestroyCharacter(character);
                    // RemoveCharacterFromGame(game, character - game->characters);
                    character->x = random() % (SCREEN_WIDTH);
                    character->x = random() % (SCREEN_HEIGHT);
                    free(character);
                    // break;
                }
    }

    GameInputs(game);
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
void SpawnEnemy(struct Game *game)
{
    int rX = random() % (0 - SCREEN_WIDTH);
    int rY = random() % (0 - SCREEN_HEIGHT);
    CreateCharacter(&game, rX, rY, 1, &sansSprite, PAL0, AI);
}
