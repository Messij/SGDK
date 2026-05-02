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
    CreateCharacter(&game, SCREEN_WIDTH - 50, SCREEN_HEIGHT - 50, 2, &sansSprite, PAL3, JOY_2);

    // PNJs
    // CreateCharacter(&game, 100, 100, 1, &friskSprite,PAL3, AI);

    while (game.isRunning)
    {
        // UPDATE
        UpdateGame(&game);

        // DRAW
        DrawGame(&game);
    }
    return (0);
}
