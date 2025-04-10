#include <stdio.h>
#include <stdbool.h>
#include "midiToFrame_init.h"
#include "userMidiCommand.h"
#include "texture_init.h"
#include "rendererMovie.h"
#include "midi/portmidi_init.h"
#include "sdl/sdl_init.h"


int map_MidiRectY(int value, int in_min, int in_max,
                    int out_min, int out_max) {
    return out_min + (value - in_min) * (out_max - out_min)
                    / (in_max - in_min);
}

void userMidiCommand (PORTMIDI_Context *portmidiContext, 
                       uint64_t tab_notestToFrames[],
                       FFmpeg_Context *ffmpegContext,
                       TIME_Context *timeContext,
                       SDL_Context *sdlContext, 
                       TEXTURE_Context *textureContext, 
                       SDLFX_Context *sdlFxContext)
{

if (!portmidiContext || !ffmpegContext || !timeContext || 
    !sdlContext || !textureContext || !sdlFxContext) {
    return;
}

    portmidiContext->error = Pm_Read(portmidiContext->midiStream, 
                                &portmidiContext->event, 1);

    if (portmidiContext->error == 1) {
        int status = Pm_MessageStatus(portmidiContext->event.message);
        int channel = (status & 0x0F);
        int note = Pm_MessageData1(portmidiContext->event.message);
        int velocity = Pm_MessageData2(portmidiContext->event.message);

        printf("MIDI received: Status=%d, Channel=%d," 
               " Note=%d, Velocity=%d\n",
               status & 0xF0, channel + 1, note, velocity);

        // Canal 16 (canal 15 en 0-indexé)
        if (channel == 0x0F) {
            // Note On hors  127
            if ((status & 0xF0) == 0x90  && note != 127) {
                if (note >= 0 && note < 128 
                              && tab_notestToFrames[note] != UINT64_MAX) {
                    framePV(ffmpegContext, tab_notestToFrames[note]);
                } else {
                    printf("Note %d ignorée :" 
                           " hors plage ou non mappée\n",note);
                }
            }

            // Note Off
            else if ((status & 0xF0) == 0x80 && note != 127) {
                ffmpegContext->isPlaying = 0;

                if (ffmpegContext->codecContext) {
                    avcodec_flush_buffers(ffmpegContext->codecContext);
                }

                timeContext->frameCounter = 0;
                SDL_SetRenderDrawColor(sdlContext->renderer, 0, 0, 0, 0);
            }

            // Note 127 = flash
            else if ((status & 0xF0) == 0x90 && note == 127) {
                sdlFxContext->isWhiteRectVisible = true;
            }

        }
        // ecran noir ciné filtre
        if ((Pm_MessageStatus(portmidiContext->event.message) & 0x0F) == 
                                0x02 && // Channel 3
                (Pm_MessageStatus(portmidiContext->event.message) & 0xF0)
                            == 0xB0 && // controleur
                Pm_MessageData1(portmidiContext->event.message) == 29)
                                                        // ctrl 29
        {
            int midiValue = Pm_MessageData2(portmidiContext->event.message);
            // Conversion de la valeur MIDI en position SDL
            int windowWidth, windowHeight;
            SDL_GetRendererOutputSize(sdlContext->renderer,                     
                             &windowWidth, &windowHeight);
            int newY = map_MidiRectY(midiValue, 0, 127,
                    -windowHeight, -windowHeight / 2);
            sdlFxContext->blackRect1.y = newY;
            sdlFxContext->blackRect2.y = -newY;
        }
    }
}

