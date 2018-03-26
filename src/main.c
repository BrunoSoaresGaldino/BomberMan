
#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../include/tile_map.h"
#include "../include/bomber_man.h"
#include "../include/defs.h"
#include "../include/error.h"
#include "../include/load_resources.h"

bool exit_program = false;

void ExitProgram(  )
{
    exit_program = true;
}
END_OF_FUNCTION( ExitProgram );


void SetTic( void *tic )
{
    
    *(int *)tic = 1;
    
}
END_OF_FUNCTION( SetTic );



int main( void )
{


    BITMAP   *images[6];
    BITMAP   *buffer;
    BomberMan bomber = { .x = 1 , .y = 1 , .bomb_strenght = 1 };
    TileMap  *tile_map = TileMapNew( );
    int       tic = 0;
    char      level[ ] = "level/level1.lvl";
    int       level_count = 1;
    
    
    allegro_init( );
    install_timer( );
    install_keyboard( );
    set_color_depth(24);
    set_gfx_mode( GFX_AUTODETECT_WINDOWED, 600,600,0,0);
    install_sound( MIDI_AUTODETECT, DIGI_AUTODETECT,NULL);
    install_param_int_ex( SetTic , &tic , BPS_TO_TIMER(FRAMES_PER_SEC) );
    set_close_button_callback( ExitProgram );
    
    LOCK_VARIABLE( tic );
    LOCK_VARIABLE( exit_program);
    LOCK_FUNCTION( SetTic );
    LOCK_FUNCTION( ExitProgram );
    
    
    if( !( buffer = create_bitmap( SCREEN_W , SCREEN_H ) ) )
    {
        Abort("Nao foi possivel criar buffer",NULL);
    }
    
    images[NONE]  = NULL;
    images[WALL]  = LoadImage("img/wall.bmp");
    images[DOOR]  = LoadImage("img/door.bmp");
    images[BOMB]  = LoadImage("img/bomb.bmp");
    images[FIRE]  = LoadImage("img/fire.bmp");
    images[BLOCK] = LoadImage("img/block.bmp");
    
    bomber.skin   = LoadImage( "img/bomber.bmp");
    bomber.bombs  = ListNew( );
    bomber.explosion_fx = LoadSample("sound/boom.wav");
    
    TileMapLoadFile( tile_map,level);
    tile_map->tile_size = 40;
    
    
    while( !exit_program  )
    {
        
        if( key[KEY_ESC] )
        {
            ExitProgram( );
        }
        
        if( tic )
        {
            if( key[KEY_DOWN] )
            {
                key[KEY_DOWN] = 0;
                BomberManMove( &bomber, KEY_DOWN, tile_map);
            }
            
            else if( key[KEY_UP] )
            {
                key[KEY_UP] = 0;
                BomberManMove( &bomber, KEY_UP, tile_map);
            }
            
            else if( key[KEY_LEFT] )
            {
                key[KEY_LEFT] = 0;
                BomberManMove( &bomber, KEY_LEFT, tile_map);
            }
            else if( key[KEY_RIGHT] )
            {
                key[KEY_RIGHT] = 0;
                BomberManMove( &bomber, KEY_RIGHT, tile_map);
            }
            
            if( key[KEY_SPACE] )
            {
                key[KEY_SPACE] = 0;
                BomberManPlantBomb( &bomber, tile_map );
            }
            
            clear_to_color( buffer , makecol( 0, 144, 0 ) );
            
            TileMapDrawTiles( tile_map , images , buffer );
            BomberManDrawBomberMan( &bomber, buffer, tile_map->tile_size );
            draw_sprite( screen, buffer, 0, 0 );
            
            
            BomberManClearFire( tile_map );
            BomberManBombDecreaseTimeout( bomber.bombs );
            BomberManExplodeBomb( &bomber, tile_map);
            
            if( BomberManOnFire( &bomber, tile_map )  )
            {
                Warn("BomberMan explodiu",NULL);
                
                ExitProgram( );
            }
            
            if( BomberManOpenedDoor( &bomber , tile_map ) )
            {
                if( level_count < 7 )
                {
                    level_count++;
                    sprintf(level,"level/level%d.lvl",level_count);

                }
                
                TileMapLoadFile( tile_map,level);
                bomber.x = bomber.y  = 1;
                bomber.bomb_strenght = level_count;
                
            }
            
            tic = 0;
            
        }
    
    }
   
    
    return 0;

}
END_OF_MAIN( )
