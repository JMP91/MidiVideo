#include <stdio.h>
#include <stdlib.h>
#include "midi/portmidi_init.h"

PORTMIDI_Context *initPortMidi(void) {
    PORTMIDI_Context *portmidiContext = malloc(sizeof(PORTMIDI_Context));
    if (!portmidiContext) {
        fprintf(stderr, "Erreur allocation mémoire pour PORTMIDI_Context\n");
        return NULL;
    }

    portmidiContext->error = Pm_Initialize();
    if (portmidiContext->error != pmNoError) {
        fprintf(stderr, "PortMidi initialization error: %s\n",
                Pm_GetErrorText(portmidiContext->error));
        free(portmidiContext);
        return NULL;
    }

    int numDevices = Pm_CountDevices();
    if (numDevices <= 0) {
        fprintf(stderr, "Aucun périphérique MIDI détecté : %s\n",
                Pm_GetErrorText(numDevices));
        Pm_Terminate();
        free(portmidiContext);
        return NULL;
    }

    int deviceID = 3;
    if (deviceID < 0 || deviceID >= numDevices) {
        fprintf(stderr, 
                "deviceID %d hors plage. %d périphériques détectés.\n",
                deviceID, numDevices);
        Pm_Terminate();
        free(portmidiContext);
        return NULL;
    }

    const PmDeviceInfo *deviceInfo = Pm_GetDeviceInfo(deviceID);
    if (!deviceInfo) {
        fprintf(stderr, "Erreur info périphérique %d : %s\n",
                deviceID, Pm_GetErrorText(numDevices));
        Pm_Terminate();
        free(portmidiContext);
        return NULL;
    }

    portmidiContext->error = Pm_OpenInput(&(portmidiContext->midiStream),
                                        deviceID, NULL, 
                                        MIDI_BUFFER_SIZE, NULL, NULL);
    if (portmidiContext->error != pmNoError || 
                                    portmidiContext->midiStream == NULL) {
        fprintf(stderr, "Échec ouverture flux MIDI : %s\n",
                Pm_GetErrorText(portmidiContext->error));
        Pm_Terminate();
        free(portmidiContext);
        return NULL;
    }

    printf("\nPortMidi initialisé avec succès\n");
    printf("Périphérique choisi : %d (%s)\n", deviceID, deviceInfo->name);
	printPortMidi();
printf("✅ PortMidi initialisé avec succès. Context @ %p\n", (void *)portmidiContext);
    return portmidiContext;
}
void printPortMidi(void) {
    // NE PAS réinitialiser PortMidi ici si déjà fait ailleurs

    int numDevices = Pm_CountDevices();
    if (numDevices < 0) {
        fprintf(stderr, "Erreur récupération périphériques : %s\n", 
                Pm_GetErrorText(numDevices));
        return;
    }

    printf("\nNombre de périphériques MIDI disponibles : %d\n", numDevices);

    for (int i = 0; i < numDevices; ++i) {
        const PmDeviceInfo *info = Pm_GetDeviceInfo(i);
        if (!info) continue;

        printf("\nPériphérique %d :\n", i);
        printf("  Nom       : %s\n", info->name);
        printf("  Interface : %s\n", info->interf);
        printf("  Entrée    : %s\n", info->input ? "Oui" : "Non");
        printf("  Sortie    : %s\n", info->output ? "Oui" : "Non");

        if (i == Pm_GetDefaultInputDeviceID())
            printf("  ➤ Entrée par défaut\n");

        if (i == Pm_GetDefaultOutputDeviceID())
            printf("  ➤ Sortie par défaut\n");
    }
}
void closePortMidi(PORTMIDI_Context *portmidiContext) {
    if (!portmidiContext) return;
    if (portmidiContext->midiStream) {
        Pm_Close(portmidiContext->midiStream);
    }
    Pm_Terminate();
    free(portmidiContext);
}
