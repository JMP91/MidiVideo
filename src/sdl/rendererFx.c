#include <stdio.h>
#include <stdbool.h>
#include "sdl/sdl_init.h"
#include "core/timer_init.h"
#include "sdl/sdlFx_init.h"


void rendererFx (SDL_Context *sdlContext, 
                TIME_Context *timeContext, SDLFX_Context *sdlFxContext) {
    if (sdlFxContext->isWhiteRectVisible == true) {
        timeContext->currentTime = SDL_GetTicks();
        timeContext->elapsedTime = timeContext->currentTime 
                                    - timeContext->lastWhiteRectChangeTime;

        if (timeContext->elapsedTime < 100) {
            SDL_SetRenderDrawColor(sdlContext->renderer, 255, 255, 255, 255);
            SDL_RenderFillRect(sdlContext->renderer, 
                    &sdlFxContext->whiteRect);
        }
        else {
            sdlFxContext->isWhiteRectVisible = false;
        }
    }
    else {
        timeContext->lastWhiteRectChangeTime = SDL_GetTicks();
        SDL_SetRenderDrawColor(sdlContext->renderer, 0, 0, 0, 0);
    }
}
