#include <stdio.h>
#include <stdlib.h>
#include "sdl/sdl_init.h"
#include <stdbool.h>

SDL_Context *initSDL(int windowWidth, int windowHeight) {
    SDL_Context *sdlContext = malloc(sizeof(SDL_Context));
    if (!sdlContext) {
        fprintf(stderr, "Failed to allocate SDL context\n");
        return NULL;
    }
    if (SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Could not initialize SDL - %s\n",
                SDL_GetError());
        free(sdlContext);
        return NULL;
    }
    sdlContext->window = SDL_CreateWindow("MidiVideo",
                                        SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED,
                                        windowWidth, windowHeight, 
                                        SDL_WINDOW_SHOWN |
                                        SDL_WINDOW_ALLOW_HIGHDPI);
    if (!sdlContext->window) {
        fprintf(stderr, "SDL: could not create window - exiting\n");
        SDL_Quit();
        free(sdlContext);
        return NULL;
    }
    sdlContext->renderer = SDL_CreateRenderer(sdlContext->window, -1,
                                                SDL_RENDERER_ACCELERATED | 
                                                SDL_RENDERER_PRESENTVSYNC);
    if (!sdlContext->renderer) {
        fprintf(stderr, "SDL: could not create renderer - exiting\n");
        SDL_DestroyWindow(sdlContext->window);
        SDL_Quit();
        free(sdlContext);
        return NULL;
    }
    sdlContext->running = true;
    sdlContext->fullScreen = false;
    return sdlContext;
}

void cleanupSDL(SDL_Context *sdlContext) {
    if (sdlContext) {
        if (sdlContext->renderer) 
            SDL_DestroyRenderer(sdlContext->renderer);
        if (sdlContext->window) SDL_DestroyWindow(sdlContext->window);
        free(sdlContext);
    }
    SDL_Quit();
}
void userEvent (SDL_Context *sdlContext) {
    if (SDL_PollEvent(&sdlContext->userEvent) == 1) {
        switch (sdlContext->userEvent.type) {
            case SDL_QUIT:
                sdlContext->running = false;
                break;
        }
    }
}

