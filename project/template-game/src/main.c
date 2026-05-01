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
    CreateCharacter(&game, 5, 5, 2, &friskSprite, JOY_1);
    CreateCharacter(&game, 50, 50, 2, &friskSprite, JOY_2);

    // PNJs
    // CreateCharacter(&game, 100, 100, 1, &friskSprite, AI);

    while (game.isRunning)
    {
        // UPDATE
        UpdateGame(&game);

        // DRAW
        DrawGame(&game);
    }
    return (0);
}
