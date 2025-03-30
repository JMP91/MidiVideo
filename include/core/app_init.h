#ifndef APP_INIT_H
#define APP_INIT_H

#include "sdl_init.h"
#include "texture_init.h"
#include "ffmpeg_init.h"
#include "sdlFx_init.h"
#include "portmidi_init.h"
#include "timer_init.h"

typedef struct {
    SDL_Context *sdl;
    TEXTURE_Context *texture;
    FFmpeg_Context *ffmpeg;
    SDLFX_Context sdlFx;
    PORTMIDI_Context *midi;
    TIME_Context time;
} APP_Context;

int initApp(APP_Context *app);
void cleanupApp(APP_Context *app);

#endif 
