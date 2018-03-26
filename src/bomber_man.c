
#include "../include/bomber_man.h"

void BomberManDrawBomberMan( BomberMan *bomber, BITMAP *buffer, int tile_size )
{
    
    draw_sprite( buffer , bomber->skin , bomber->x * tile_size , bomber->y * tile_size );
    
}

void BomberManMove( BomberMan *bomber, int key , TileMap *tile_map )
{
    
    int x = bomber->x;
    int y = bomber->y;
    
    int code;
    
    if( key == KEY_DOWN )
    {
        code = ( tile_map->tiles + x + (y+1) * tile_map->h )->code;
        
        if( code == NONE || code == DOOR  ) 
        {
            bomber->y++;
        }

    }

    else if( key == KEY_UP )
    {
        code = ( tile_map->tiles + x + (y-1) * tile_map->h )->code;
        
        if( code == NONE || code == DOOR  )
        {
            bomber->y--;
        }
    }

    else if( key == KEY_RIGHT )
    {
        code  = (tile_map->tiles + x+1 + y*tile_map->h )->code;
        
        if( code == NONE || code == DOOR )
        {
            bomber->x++;
        }

    }

    else if( key == KEY_LEFT )
    {
        code = (tile_map->tiles + (x-1) + y * tile_map->h )->code;
        
        if( code == NONE || code == DOOR )
        {
            bomber->x--;
        }

    }
   
    
}

void BomberManPlantBomb( BomberMan *bomber, TileMap *tile_map )
{
    
    Bomb *bomb = malloc( sizeof(Bomb) );
    
    if( bomb )
    {
        bomb->x = bomber->x;
        bomb->y = bomber->y;
        bomb->strenght = bomber->bomb_strenght;
        bomb->timeout = FRAMES_PER_SEC * bomb->strenght / 2;
        bomb->explode = false;

        TileMapTileSetCode( tile_map , bomb->x, bomb->y, BOMB );
        ListInsert( bomber->bombs, bomb , free );

    }
    
}

void BomberManExplodeBomb(BomberMan *bomber, TileMap *tile_map )
{
    
    Bomb *bomb;
    int   code;
    int   x;
    int   y;
    int   i;
    int   j;
    int   k;
    
    while( ( bomb = ListGetNext( bomber->bombs ) ) )
    {
       
        if( bomb->explode )
        {
            x = bomb->x;
            y = bomb->y;
            
            ListRemoveByIndex( bomber->bombs, 0, true );// a primeira bomba plantada  é a primeira a explodir( Óbvio)

            TileMapTileSetCode( tile_map, x, y, FIRE );
            
            play_sample( bomber->explosion_fx, 255,128,1000,0);

            for( i = y-1, j = y+1, k = 0 ; k < bomb->strenght ; k++ )
            {

                code = TileMapTileGetCode( tile_map , x , j );

                if( code != BLOCK  && code != INVALID && code != BOMB && code != DOOR )
                {

                    TileMapTileSetCode( tile_map , x, j , FIRE );
                    j++;
                    
                }

                code = TileMapTileGetCode( tile_map , x , i );

                if( code  != BLOCK && code != INVALID && code != BOMB && code != DOOR )
                {

                    TileMapTileSetCode( tile_map , x,  i , FIRE );
                    i--;
                    
                }
                
            }
            
            for( i = x-1, j = x+1, k = 0 ; k < bomb->strenght ; k++ )
            {

                code = TileMapTileGetCode( tile_map , j , y );

                if( code != BLOCK  && code != INVALID && code != BOMB && code != DOOR )
                {

                    TileMapTileSetCode( tile_map , j, y , FIRE );
                    j++;
                    
                }

                code = TileMapTileGetCode( tile_map , i , y );

                if( code  != BLOCK && code != INVALID && code != BOMB && code != DOOR )
                {

                    TileMapTileSetCode( tile_map , i,  y , FIRE );
                    i--;
                    
                }
                
            }            
        }
        
    }

    
}

void BomberManBombDecreaseTimeout( List *bombs )
{
    
    Bomb *bomb;
    
    while( ( bomb = ListGetNext( bombs ) ) )
    {
 
        if( --bomb->timeout == 0 )
        {
            
            bomb->explode = true;
            
        }

    }
    
}

void BomberManClearFire( TileMap *tile_map )
{
    
    static time_t last_time = 0;
    time_t now = time( NULL );
    int i,j;
    
    if( difftime( now , last_time ) < 0.5 )
    {
        return;
    }
    
    last_time = now;

    for( i = 0 ; i < tile_map->h ; i++  )
    {
        for( j = 0 ; j < tile_map->w ; j++  )
        {
            if( TileMapTileGetCode( tile_map , i, j ) == FIRE )
            {
                TileMapTileSetCode( tile_map , i, j , NONE );
            }
        }
    }
}

bool BomberManOnFire( BomberMan *bomber, TileMap *tile_map )
{

    return TileMapTileGetCode( tile_map, bomber->x, bomber->y ) == FIRE;

}

bool BomberManOpenedDoor( BomberMan * bomber , TileMap *tile_map )
{
    
    return TileMapTileGetCode( tile_map, bomber->x, bomber->y ) == DOOR;
    
}