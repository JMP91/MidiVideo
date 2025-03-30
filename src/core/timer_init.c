#include "timer_init.h"


void initTimeContext (TIME_Context *timeContext)
{
    timeContext->lastWhiteRectChangeTime = SDL_GetTicks();
    timeContext->lastFrameDisplayTime = SDL_GetTicks();
    timeContext->elapsedTime = 0;
    timeContext->currentTime = 0;
    timeContext->frameCounter = 0;
}

