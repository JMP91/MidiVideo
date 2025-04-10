#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "sdl/sdl_init.h"
#include "sdl/texture_init.h"

TEXTURE_Context *texture_init (SDL_Context *sdlContext) {

    TEXTURE_Context *textureContext = malloc (sizeof(TEXTURE_Context));
    if (!textureContext) {
        fprintf(stderr, "Failes to allocat TEXTURE_Context\n");
        return NULL;
    }

    int windowWidth, windowHeight;
    SDL_GetRendererOutputSize(sdlContext->renderer, 
                                &windowWidth, &windowHeight);
    textureContext->video_T = SDL_CreateTexture(sdlContext->renderer,
                                            SDL_PIXELFORMAT_YV12,
                                            SDL_TEXTUREACCESS_STREAMING,
                                            windowWidth, windowHeight);
    if (!textureContext->video_T) {
        fprintf(stderr, "SDL: could not create texture: %s\n", 
                SDL_GetError());
        free(textureContext);
        return NULL; 
    }    
    
 
    return textureContext;
}


void cleanupTexture (TEXTURE_Context *textureContext) {

    if (textureContext) {     
        if (textureContext->video_T)
            SDL_DestroyTexture(textureContext->video_T);
    }
}
