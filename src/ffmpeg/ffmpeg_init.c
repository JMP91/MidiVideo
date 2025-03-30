#include <stdio.h>
#include <stdlib.h>
#include "ffmpeg/ffmpeg_init.h"
#include <stdbool.h>


FFmpeg_Context *initFFmpeg(const char *filename){
    FFmpeg_Context *ffmpegContext = malloc(sizeof(FFmpeg_Context));    
    if (!ffmpegContext){
        fprintf(stderr, "Failed to allocate FFmpeg context\n");
        return NULL;
    }

    ffmpegContext->formatContext = avformat_alloc_context();
    if (!ffmpegContext->formatContext){
        fprintf(stderr, "Failed to allocate format context\n");
        free(ffmpegContext);
        return NULL;
    }

    if (avformat_open_input(&ffmpegContext->formatContext, filename, NULL, NULL) != 0){
        fprintf(stderr, "Could not open video file\n");
        avformat_free_context(ffmpegContext->formatContext);
        free(ffmpegContext);
        return NULL;
    }

    if (avformat_find_stream_info(ffmpegContext->formatContext, NULL) < 0){
        fprintf(stderr, "Could not find stream information\n");
        avformat_close_input(&ffmpegContext->formatContext);
        free(ffmpegContext);
        return NULL;
    }

    // Recherche le flux vidéo dans le contexte de format
    ffmpegContext->videoStreamIndex = -1;

    for (unsigned int i = 0; i < ffmpegContext->formatContext->nb_streams; i++){
        if (ffmpegContext->formatContext->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO){
            ffmpegContext->videoStreamIndex = i;
            break;
        }
    }

    if (ffmpegContext->videoStreamIndex == -1){
        fprintf(stderr, "Could not find video stream\n");
        avformat_close_input(&ffmpegContext->formatContext);
        free(ffmpegContext);
        return NULL;
    }

    // Trouve et ouvre le codec approprié pour décoder le flux vidéo
    ffmpegContext->codec = avcodec_find_decoder(ffmpegContext->formatContext->streams[ffmpegContext->videoStreamIndex]->codecpar->codec_id);
    
    if (ffmpegContext->codec == NULL){
        fprintf(stderr, "Unsupported codec!\n");
        avformat_close_input(&ffmpegContext->formatContext);
        free(ffmpegContext);
        return NULL;
    }

    ffmpegContext->codecContext = avcodec_alloc_context3(ffmpegContext->codec);
    
    if (!ffmpegContext->codecContext){
        fprintf(stderr, "Failed to allocate codec context\n");
        avformat_close_input(&ffmpegContext->formatContext);
        free(ffmpegContext);
        return NULL;
    }

    if (avcodec_parameters_to_context(ffmpegContext->codecContext,
         ffmpegContext->formatContext->streams[ffmpegContext->videoStreamIndex]->codecpar) < 0){
        fprintf(stderr, "Failed to copy codec parameters to codec context\n");
        avcodec_free_context(&ffmpegContext->codecContext);
        avformat_close_input(&ffmpegContext->formatContext);
        free(ffmpegContext);
        return NULL;
    }

    if (avcodec_open2(ffmpegContext->codecContext, ffmpegContext->codec, NULL) < 0){
        fprintf(stderr, "Could not open codec\n");
        avcodec_free_context(&ffmpegContext->codecContext);
        avformat_close_input(&ffmpegContext->formatContext);
        free(ffmpegContext);
        return NULL;
    }

    ffmpegContext->frame = av_frame_alloc();
    
    if (!ffmpegContext->frame){
        fprintf(stderr, "Could not allocate video frame\n");
        avcodec_free_context(&ffmpegContext->codecContext);
        avformat_close_input(&ffmpegContext->formatContext);
        free(ffmpegContext);
        return NULL;
    }

    // calcule de la frame delay
    ffmpegContext->fps = av_q2d(ffmpegContext->formatContext->streams[ffmpegContext->videoStreamIndex]->avg_frame_rate);
    ffmpegContext->frameDelay = 1000 / ffmpegContext->fps;

    ffmpegContext->isPlaying = false;
    ffmpegContext->currentFrameTimestamp = 0;
    ffmpegContext->currentFrameNumber = 0;

    return ffmpegContext;
}

void cleanupFFmpeg (FFmpeg_Context *ffmpegContext){
    if (ffmpegContext){
        av_frame_free(&ffmpegContext->frame);
        avcodec_close(ffmpegContext->codecContext);
        avcodec_free_context(&ffmpegContext->codecContext);
        avformat_close_input(&ffmpegContext->formatContext);
        avformat_free_context(ffmpegContext->formatContext);
        free(ffmpegContext);
    }
}

