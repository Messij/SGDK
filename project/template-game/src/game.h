#include <genesis.h>

/// ---------------------------------- GAME ----------------------------------
struct Game
{
    // Game state variables
    bool isRunning;
    int score;
    int level;
};

void InitGame(struct Game *game)
{
    if (game == NULL)
        return;

    game->isRunning = true;
    game->score = 0;
    game->level = 1;

    // Init Sprite
    SPR_init();

    JOY_init();

    VDP_init();
    VDP_drawText("Hello Sega!!", 0, 0);
}

void DrawGame(struct Game *game)
{
    // Draw sprites
    SPR_update();

    SYS_doVBlankProcess();
}
