/**
 * Hello World Example
 * Created With Genesis-Code extension for Visual Studio Code
 * Use "Genesis Code: Compile" command to compile this program.
 **/
#include <genesis.h>
#include "resources.h"

u16 index = TILE_USER_INDEX;
Map* level_1_map;

int mapX = 0;
int mapY = 768;
int scroollSpeed = 2;

int main()
{
    VDP_loadTileSet(&tileset, index, DMA);
    level_1_map = MAP_create(&map, BG_B, TILE_ATTR_FULL(PAL0, 0, 0, 0, index));
    PAL_setPalette(PAL0, palette.data, DMA);


    while(1)
    {
        MAP_scrollTo(level_1_map, mapX, mapY);

        mapX += scroollSpeed;

        //For versions prior to SGDK 1.60 use VDP_waitVSync instead.
        SYS_doVBlankProcess();
    }
    return (0);
}
