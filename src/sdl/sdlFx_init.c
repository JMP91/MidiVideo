#include "sdl/sdl_init.h"
#include "sdl/sdlFx_init.h"
#include <stdbool.h>
#include <stdio.h>


void sdlFx_init (SDL_Context *sdlContext, 
                SDLFX_Context *sdlFxContext) {

    int windowWidth, windowHeight;
    SDL_GetRendererOutputSize(sdlContext->renderer,
                            &windowWidth, &windowHeight);
    
    sdlFxContext->whiteRect = (SDL_Rect){0, 0, windowWidth, windowHeight};
    sdlFxContext->isWhiteRectVisible = false; 

}
