#include <stdio.h>
#include <stdint.h>
#include "app_init.h"             
#include "userKeyCommand.h"
#include "rendererMovie.h"
#include "rendererFx.h"
#include "midiToFrame_init.h"
#include "userMidiCommand.h"

int main(void) {
    APP_Context app;
    if (initApp(&app) != 0) {
        fprintf(stderr, 
                "Erreur lors de l'initialisation de l'application\n");
        return -1;
    }

    uint64_t midiNoteToFrameMap[128];
    init_midiNoteToFrameMap(midiNoteToFrameMap);

    while (app.sdl->running) {

        userEvent(app.sdl);
        userKeyCommand(app.sdl, app.ffmpeg, &app.time, &app.sdlFx);
        userMidiCommand(app.midi, midiNoteToFrameMap, app.ffmpeg,
                &app.time, app.sdl, app.texture, &app.sdlFx);

        app.time.currentTime = SDL_GetTicks();
        app.time.elapsedTime = app.time.currentTime -
                               app.time.lastFrameDisplayTime;

        if (app.time.elapsedTime >= app.ffmpeg->frameDelay / 2) {
            SDL_RenderClear(app.sdl->renderer);
            rendererMovie(app.sdl, app.ffmpeg, &app.time, app.texture);
            rendererFx(app.sdl, &app.time, &app.sdlFx);
            SDL_RenderPresent(app.sdl->renderer);
            app.time.lastFrameDisplayTime = SDL_GetTicks();
        }

        SDL_Delay(1);
    }

    cleanupApp(&app);
    return 0;
}
