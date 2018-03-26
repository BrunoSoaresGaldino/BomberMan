
#ifndef TILE_MAP_H
#define TILE_MAP_H


#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>

#include "error.h"
#include "defs.h"

typedef struct
{
    
    int code;

} Tile;


typedef struct
{
    int w;// width
    int h;//height
    
    Tile *tiles;
    int tile_size;
    
} TileMap;


TileMap *TileMapNew( void );

void TileMapLoadFile( TileMap *tile_map, const char *file_name );

void TileMapDrawTiles( TileMap *tile_map, BITMAP **images ,BITMAP *buffer );

int TileMapTileGetCode( TileMap *tile_map , int x, int y);

void TileMapTileSetCode( TileMap *tile_map , int x, int y , int code );

#endif