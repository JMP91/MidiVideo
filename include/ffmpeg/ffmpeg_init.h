#ifndef FFMPEG_INIT_H
#define FFMPEG_INIT_H

#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct FFmpeg_Context {
    int64_t currentFrameTimestamp;
    int64_t currentFrameNumber;
    double fps;
    int16_t frameDelay;
    bool isPlaying;
    AVPacket videoPacket;
    AVFormatContext *formatContext;
    AVCodecContext *codecContext;
    AVCodec const *codec;
    AVFrame  *frame;
    int8_t videoStreamIndex;
} FFmpeg_Context;

FFmpeg_Context *initFFmpeg (const char *filename);
void cleanupFFmpeg (FFmpeg_Context *ffmpegContext);

#endif
