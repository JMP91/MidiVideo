#include <stdio.h>
#include "core/app_init.h"

int initApp(APP_Context *app) {
    app->ffmpeg = initFFmpeg("F.mp4");
    if (!app->ffmpeg) {
        fprintf(stderr, "Erreur : initFFmpeg a échoué\n");
        return -1;
    }

    app->sdl = initSDL(960, 540);
    if (!app->sdl) {
        fprintf(stderr, "Erreur : initSDL a échoué\n");
        cleanupFFmpeg(app->ffmpeg);
        return -1;
    }

    app->texture = texture_init(app->sdl);
    if (!app->texture) {
        fprintf(stderr, "Erreur : texture_init a échoué\n");
        cleanupSDL(app->sdl);
        cleanupFFmpeg(app->ffmpeg);
        return -1;
    }

    sdlFx_init(app->sdl, &app->sdlFx); 

    app->midi = initPortMidi();
    if (!app->midi) {
        fprintf(stderr, "Erreur : initPortMidi a échoué\n");
        cleanupTexture(app->texture);
        cleanupSDL(app->sdl);
        cleanupFFmpeg(app->ffmpeg);
        return -1;
    }

    initTimeContext(&app->time);

    return 0;
}

void cleanupApp(APP_Context *app) {
    closePortMidi(app->midi);
    cleanupTexture(app->texture);
    cleanupSDL(app->sdl);
    cleanupFFmpeg(app->ffmpeg);
}

