#ifndef SDLFX_INIT_H
#define SDLFX_INIT_H

#include <stdint.h>
#include "sdl_init.h"

typedef struct SDLFX_Context {
    int8_t isWhiteRectVisible;
    SDL_Rect whiteRect;
    SDL_Rect blackRect1;
    SDL_Rect blackRect2;
} SDLFX_Context;

void sdlFx_init (SDL_Context *sdlContext, SDLFX_Context *sdlFxContext);

#endif
