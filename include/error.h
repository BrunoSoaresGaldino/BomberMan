#ifndef ERROR_H
#define ERROR_H

#include <stdlib.h>
#include <allegro.h>

void Warn( const char *message1 , const char *message2 );
void Abort( const char *message1 , const char *message2 );

#endif