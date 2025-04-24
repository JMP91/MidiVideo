#include "utils.h"

char *find_video_filename(void) {
    const char *extensions[] = {".mp4", ".avi", ".mov", ".mkv", NULL};
    DIR *dir = opendir(".");
    if (!dir) {
        perror("Erreur lors de l'ouverture du dossier courant");
        return NULL;
    }

    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL) {
        for (int i = 0; extensions[i] != NULL; i++) {
            const char *ext = extensions[i];
            size_t len_entry = strlen(entry->d_name);
            size_t len_ext = strlen(ext);

            if (len_entry > len_ext &&
                strcmp(entry->d_name + len_entry - len_ext, ext) == 0) {
                char *filename = malloc(len_entry + 1);
                if (filename) {
                    strcpy(filename, entry->d_name);
                }
                closedir(dir);
                return filename;
            }
        }
    }

    closedir(dir);
    return NULL;
}

