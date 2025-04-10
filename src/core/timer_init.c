#include "timer_init.h"

void initTimeContext (TIME_Context *timeContext) {
    timeContext->lastFrameDisplayTime = 0;
    timeContext->lastWhiteRectChangeTime = 0;
    timeContext->elapsedTime = 0;
    timeContext->currentTime = 0;
    timeContext->frameCounter = 0;

}
