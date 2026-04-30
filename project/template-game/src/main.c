/**
 * Hello World Example
 * Created With Genesis-Code extension for Visual Studio Code
 * Use "Genesis Code: Compile" command to compile this program.
 **/
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

    // PLAYER 1
    struct Character player;
    InitCharacter(&player, 5, 5, 2, &friskSprite, JOY_1);

    // PLAYER 2
    struct Character player2;
    InitCharacter(&player2, 50, 50, 2, &friskSprite2, JOY_2);

    // PNJ1
    // PNJ2

    while (game.isRunning)
    {
        // UPDATE
        UpdateCharacter(&player);
        UpdateCharacter(&player2);

        // DRAW
        DrawGame(&game);
    }
    return (0);
}
