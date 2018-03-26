
# include "../include/load_resources.h"

BITMAP *LoadImage( const char *file_name )
{
    
    BITMAP *image = load_bitmap( file_name, NULL );
    
    if( image )
    {
        return image;
    }
    
    Abort(file_name," >> Erro ao ler imagem");
    
}

SAMPLE *LoadSample( const char *file_name)
{
    
    SAMPLE *sample = load_sample( file_name );
    
    if( sample )
    {
        return sample;
    }
    
    Abort( file_name, " >> Erro ao ler sample");
    
}