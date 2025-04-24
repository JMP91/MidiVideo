#include <stdio.h>
#include "core/utils.h"
#include "core/app_init.h"




int initApp(APP_Context *app) {

    char *video_name = find_video_filename();
    if (!video_name) {
        fprintf(stderr, "Aucune vidéo trouvée.\n");
        exit(1); // ou une gestion d’erreur propre à ton app
    }

    app->ffmpeg = initFFmpeg(video_name);
    if (!app->ffmpeg) {
        fprintf(stderr, "Erreur : initFFmpeg a échoué\n");
        return -1;
    }

    free(video_name);

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

