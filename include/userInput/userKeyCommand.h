#ifndef USERKEYCOMMAND_H
#define USERKEYCOMMAND_H

#include "sdl_init.h"
#include "ffmpeg_init.h"
#include "timer_init.h"
#include "sdlFx_init.h"
#include "texture_init.h"

void userKeyCommand (SDL_Context *sdlContext, FFmpeg_Context *ffmpegContext, TIME_Context *timeContext, SDLFX_Context *sdlFxContext);

#endif
