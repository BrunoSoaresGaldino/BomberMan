
#ifndef LOAD_RESOURCES_H
#define LOAD_RESOURCES_H

#include <allegro.h>
#include "error.h"

BITMAP *LoadImage( const char *file_name );
SAMPLE *LoadSample( const char *file_name);

#endif