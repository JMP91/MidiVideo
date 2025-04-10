#ifndef USERMIDICOMMAND_H
#define USERMIDICOMMAND_H

#include "ffmpeg_init.h"
#include "sdl_init.h"
#include "timer_init.h"
#include "portmidi_init.h"
#include "midiToFrame_init.h"
#include "texture_init.h"
#include "sdlFx_init.h"


void userMidiCommand (PORTMIDI_Context *portmidiContext, 
                     uint64_t tab_notestToFrames[],
                     FFmpeg_Context *ffmpegContext, 
                     TIME_Context *timeContext,
                     SDL_Context *sdlContext, 
                     TEXTURE_Context *textureContext, 
                     SDLFX_Context *sdlFxContext);

int map_MidiRectY (int value, int in_min, int in_max,
                    int out_min, int out_max); 
#endif
