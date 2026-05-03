#include <genesis.h>
#include "resources.h"
#include "game.h"
#include "factory.h"

/// ---------------------------------- MAIN ----------------------------------
int main()
{
    // GAME
    struct Game game;
    InitGame(&game);

    // PLAYERS
    CreateCharacter(&game, 5, 5, 2, &friskSprite, PAL2, JOY_1);
    // CreateCharacter(&game, SCREEN_WIDTH - 50, SCREEN_HEIGHT - 50, 2, &sansSprite, PAL3, JOY_2);

    // PNJs
    // int rX = random() % (SCREEN_WIDTH);
    // int rY = random() % (SCREEN_HEIGHT);
    // CreateCharacter(&game, rX, rY, 1, &sansSprite, PAL0, AI);
    // SpawnEnemy(&game);

    while (game.isRunning)
    {
        // UPDATE
        UpdateGame(&game);

        // DRAW
        DrawGame(&game);
    }
    return (0);
}
