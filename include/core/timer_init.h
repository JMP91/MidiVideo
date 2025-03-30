#ifndef TIMER_INIT_H 
#define TIMER_INIT_H 

#include "sdl_init.h"
#include <stdint.h>

typedef struct TIME_Context {
    int32_t lastWhiteRectChangeTime;
    int8_t frameCounter;
    int32_t lastFrameDisplayTime;
    int32_t elapsedTime;
    int32_t currentTime;
} TIME_Context;

void initTimeContext (TIME_Context *timeContext);

#endif
