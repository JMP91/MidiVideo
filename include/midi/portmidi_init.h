#ifndef PORTMIDI_INIT_H
#define PORTMIDI_INIT_H

#include <portmidi.h>

#define MIDI_BUFFER_SIZE 1024

typedef struct PORTMIDI_Context {

    PmEvent event;
    PmError error;
    PmStream *midiStream;

} PORTMIDI_Context;

PORTMIDI_Context *initPortMidi (void);
void printPortMidi ();
void closePortMidi (PORTMIDI_Context *portmidiContext);

#endif
