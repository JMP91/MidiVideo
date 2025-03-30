#ifndef RENDERER_MOVIE_H
#define RENDERER_MOVIE_H


#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <stdint.h>
#include "texture_init.h"

void framePV (FFmpeg_Context *ffmpegContext, int64_t frameNUmber);
void rendererMovie (SDL_Context *sdlContext, FFmpeg_Context *ffmpegContext, TIME_Context *timeContext, TEXTURE_Context *textureContext);


#endif
