#ifndef TEXTURE_INIT_H
#define TEXTURE_INIT_H

#include <stdint.h>
#include "sdl_init.h"

typedef struct TEXTURE_Context {

    SDL_Texture *video_T;

} TEXTURE_Context;

TEXTURE_Context *texture_init (SDL_Context *sdlContext);
void cleanupTexture (TEXTURE_Context *textureContext);


#endif
