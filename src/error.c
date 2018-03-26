
#include "../include/error.h"

void Warn( const char *message1 , const char *message2  )
{

    char    *message;
    int     color_depth;
    int     screen_width;
    int     screen_height;
    
    if( message1 && message2 )
    {
        message = malloc( strlen( message1) + strlen( message2 ) + 1 );
        *message = '\0';
        strcat( message , message1 );
        strcat( message , message2 );
    }
    
    else if( message1 )
    {
        message = (char*)message1;
    }
    
    else if( message2 )
    {
        message = (char*)message2;
    }
    else
    {
        return;
    }
    
    
    if( screen )// modo grafico ativado
    {
        
        color_depth = get_color_depth( );
        screen_width = SCREEN_W;
        screen_height = SCREEN_H;
        
        set_gfx_mode( GFX_TEXT , 0, 0, 0 ,0 );
        
        allegro_message( message );
        
        set_color_depth( color_depth );
        set_gfx_mode( GFX_AUTODETECT_WINDOWED, screen_width , screen_height , 0, 0 );
    
        return;
    }
    
    allegro_message( message );
}

void Abort( const char *message1 , const char *message2 )
{
    char    *message;

    if( message1 && message2 )
    {
        message = malloc( strlen( message1) + strlen( message2 ) + 1 );
        *message = '\0';
        strcat( message , message1 );
        strcat( message , message2 );
    }
    
    else if( message1 )
    {
        message = (char*)message1;
    }
    
    else if( message2 )
    {
        message = (char*)message2;
    }
    
    
    if( screen && message )
    {
        set_gfx_mode( GFX_TEXT, 0, 0, 0,0 );
        allegro_message( message );
    }
    
    exit( EXIT_FAILURE);
    
}