
#ifndef BOMBER_MAN_H
#define BOMBER_MAN_H

#include <time.h>

#include "tile_map.h"
#include "list.h"
#include "defs.h"


typedef struct
{
    
    int  x;
    int  y;
    int  timeout;
    int  strenght;
    bool explode;
    
} Bomb;


typedef struct
{
    
    int     x;
    int     y;
    int     bomb_strenght;
    BITMAP *skin;
    SAMPLE *explosion_fx;
    List   *bombs;
    
} BomberMan;


void BomberManDrawBomberMan( BomberMan *bomber , BITMAP *buffer , int tile_size);

void BomberManMove( BomberMan *bomber, int key , TileMap *tile_map );

void BomberManPlantBomb( BomberMan *bomber, TileMap *tile_map );

void BomberManExplodeBomb( BomberMan *bomber, TileMap *tile_map );

void BomberManBombDecreaseTimeout( List *bombs );

void BomberManClearFire( TileMap *tile_map );

bool BomberManOnFire( BomberMan *bomber, TileMap *tile_map );

bool BomberManOpenedDoor( BomberMan *bomber, TileMap *tile_map );

#endif