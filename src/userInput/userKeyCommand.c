#include <stdio.h>
#include <stdbool.h>
#include "sdl/sdl_init.h"
#include "ffmpeg/ffmpeg_init.h"
#include "core/timer_init.h"
#include "sdl/rendererMovie.h"
#include "userInput/userKeyCommand.h"
#include "sdl/sdlFx_init.h"



void userKeyCommand (SDL_Context *sdlContext, FFmpeg_Context *ffmpegContext, TIME_Context *timeContext, SDLFX_Context *sdlFxContext) {    

    switch (sdlContext->userEvent.type) {
        case SDL_KEYDOWN:
            switch (sdlContext->userEvent.key.keysym.sym) {
                case SDLK_a:
                    framePV(ffmpegContext, 0);
                    fflush(stdout);
                    break;
                case SDLK_z:
                    framePV(ffmpegContext, 4501);
                    break;
                case SDLK_e:
                    framePV(ffmpegContext, 15800);
                    break;

                case SDLK_SPACE:
                    ffmpegContext->isPlaying = false;
                    avcodec_flush_buffers(ffmpegContext->codecContext);
                    timeContext->frameCounter = 0;
                    break;

                    case SDLK_p:
                    sdlFxContext->isWhiteRectVisible = true;
                    break;
					case SDLK_f:
                        if (sdlContext->fullScreen == false) {
                           SDL_SetWindowFullscreen(sdlContext->window, SDL_WINDOW_FULLSCREEN_DESKTOP);
                           SDL_ShowCursor(SDL_DISABLE);
                           int width, height;
                           SDL_GetRendererOutputSize(sdlContext->renderer, &width, &height);
                           sdlFxContext->whiteRect = (SDL_Rect){0, 0, width, height};

                        }
                        else {
                            SDL_SetWindowFullscreen(sdlContext->window, 0);
                            SDL_ShowCursor(SDL_ENABLE);
                        }
                	sdlContext->fullScreen = !sdlContext->fullScreen;
                	break;
                default:
                    break;
            }
            break; // Sortir du switch SDL_KEYDOWN
        }
}
