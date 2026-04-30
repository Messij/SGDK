

#include <genesis.h>
#include "resources.h"
#include "game.h"
#include "character.h"

/// ---------------------------------- MAIN ----------------------------------
int main()
{
    // GAME
    struct Game game;
    InitGame(&game);

    // PLAYERS
    struct Character player1;
    InitCharacter(&player1, 5, 5, 2, &friskSprite, JOY_1);
    AddCharacter(&game, &player1);

    struct Character player2;
    InitCharacter(&player2, 50, 50, 2, &friskSprite, JOY_2);
    AddCharacter(&game, &player2);

    // PNJs
    struct Character pnj1;
    InitCharacter(&pnj1, 100, 100, 1, &friskSprite, AI);
    AddCharacter(&game, &pnj1);
    // struct Character pnj2;
    // InitCharacter(&pnj2, 150, 150, 1, &friskSprite, AI);
    // AddCharacter(&game, &pnj2);

    while (game.isRunning)
    {
        // UPDATE
        UpdateGame(&game);

        // DRAW
        DrawGame(&game);
    }
    return (0);
}
