
#include "../include/tile_map.h"


TileMap *TileMapNew( void )
{
    
    return calloc( 1, sizeof(TileMap) );
    
}

void TileMapLoadFile( TileMap *tile_map, const char *file_name )
{
    
    FILE    *file = fopen( file_name ,"r");
    
    int width;
    int height;
    
    if( file )
    {
        
        if(  fscanf( file, "%d%d", &width , &height, &height )  < 0 )
        {
            Abort( file_name ," >> Dimensoes do mapa nao encotradas" );
        }
        
        if( width != tile_map->w || height != tile_map->h )
        {
            tile_map->w = width;
            tile_map->h = height;
            
            if( tile_map->tiles )
            {
                free( tile_map->tiles );
            }
            
            if( !( tile_map->tiles = malloc( width * height * sizeof(Tile) ) ) )
            {
                Abort("Sem memoria",NULL);
            }
        
        }

        for( int i = 0 ; i < width * height ; i++ )
        {
            if(  fscanf( file,"%d", &tile_map->tiles[i].code ) < 0 )
            {
                Abort( file_name, " >> Mapa de tile incompleto" );
            }
            
        }
        
        fclose( file );
        return;

    }

    Abort( file_name ," >> Nao foi possivel abrir o arquivo");
    
}

void TileMapDrawTiles( TileMap *tile_map, BITMAP **images , BITMAP *buffer )
{

    int code;
    
    for( int i = 0; i < tile_map->h; i++ )
    {
        for( int j = 0; j < tile_map->w; j++ )
        {
            code = (tile_map->tiles + j + i * tile_map->h )->code;
            
            if( code )// zero , não desenha
            {
                draw_sprite( buffer, images[ code ] , j * tile_map->tile_size, i * tile_map->tile_size );
            }
            
        }
    
    }
    
}

int TileMapTileGetCode( TileMap *tile_map , int x, int y )
{
    
    if( x >= 0  && x < tile_map->h  && y >= 0 && y < tile_map->w )
    {
        return ( tile_map->tiles + x + y * tile_map->h )->code;
    }
    
    return INVALID;
}

void TileMapTileSetCode( TileMap *tile_map , int x, int y , int code )
{
    
    (tile_map->tiles + x + y * tile_map->h )->code = code;
    
}