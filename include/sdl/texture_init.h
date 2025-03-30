#ifndef TEXTURE_INIT_H
#define TEXTURE_INIT_H

#include <stdint.h>
struct SDL_Context; 

typedef struct TEXTURE_Context {

//    int8_t isWhiteRectVisible;
//    SDL_Rect whiteRect;
    SDL_Texture *video_T;

} TEXTURE_Context;

TEXTURE_Context *texture_init (struct SDL_Context *sdlContext);

void cleanupTexture (TEXTURE_Context *textureContext);


#endif
