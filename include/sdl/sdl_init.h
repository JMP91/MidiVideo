#ifndef SDL_INIT_H
#define SDL_INIT_H

#include <SDL2/SDL.h>
#include <stdbool.h>

typedef struct SDL_Context {
    bool running;
    bool fullScreen; 
    SDL_Event userEvent;
    SDL_Window *window;
    SDL_Renderer *renderer;
} SDL_Context;

SDL_Context *initSDL(int windowWidth, int windowHeight);
void cleanupSDL(SDL_Context *sdlContext);
void userEvent (SDL_Context *sdlContext);

#endif 
