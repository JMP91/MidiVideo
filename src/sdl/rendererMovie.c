#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "core/timer_init.h"
#include "sdl/sdl_init.h"
#include "sdl/texture_init.h"
#include "ffmpeg/ffmpeg_init.h"
#include "sdl/rendererMovie.h"



// fonction qui place la tete a la bonne frame precise 
void framePV(FFmpeg_Context *ffmpegContext, int64_t frameNUmber) {

    ffmpegContext->currentFrameNumber = frameNUmber + 1 ; // car avread
                                                    //read la frame d apres
    
    // Calcule de la target de manière approximative 
    // AV_TIME_BASE est en micro donc pas milli donc /100
    int64_t target_pts = frameNUmber * ffmpegContext->formatContext
                        ->streams[ffmpegContext->videoStreamIndex]
                        ->time_base.den / ffmpegContext->fps;

    // deplacement de la tête de lecture a la target apprximative 
    if (av_seek_frame(ffmpegContext->formatContext,
                     ffmpegContext->videoStreamIndex,
                     target_pts, 0) < 0) 
            fprintf(stderr, "Error seeking frame\n");

    // lecture jusqu à trouver le paquet qui contient
    //  le bon pts donc la tete est au bon endroit
    // placement precis de la tete .
    if (av_read_frame(ffmpegContext->formatContext, &ffmpegContext
                ->videoPacket) >= 0) {
        if (ffmpegContext->videoPacket.stream_index == ffmpegContext
                ->videoStreamIndex) {
            int ret = 1;
            while (ret != 0 && ret != AVERROR_EOF){
                avcodec_send_packet(ffmpegContext->codecContext, 
                                    &ffmpegContext->videoPacket);
                ret = avcodec_receive_frame(ffmpegContext->codecContext,
                                            ffmpegContext->frame);

                //comme le lecteur on s assure 
                //que le paqet est recu entier .
                if (ret == AVERROR(EAGAIN)) {
                    // Pas de trame disponible, lire un nouveau paquet
                    // On lit ici un nouveau paquet avant de continuer
                    if (av_read_frame(ffmpegContext->formatContext,
                                    &ffmpegContext->videoPacket) < 0) {
                        // Aucun paquet disponible, sortir de la boucle
                        break; 
                    }
                    continue; // Continue à la prochaine itération
                }
                else if (ret < 0) {
                    printf("Erreur lors de la réception de la trame:" 
                            "%s\n", 
                          av_err2str(ret));
                    break;
                }
                else if (ffmpegContext->videoPacket.pts == target_pts)
                    break;   
            }
            av_packet_unref(&ffmpegContext->videoPacket);
        }
    }

    ffmpegContext->isPlaying = true;
}

void rendererMovie (SDL_Context *sdlContext, FFmpeg_Context *ffmpegContext,
        TIME_Context *timeContext, TEXTURE_Context *textureContext) {
    if (ffmpegContext->isPlaying == true) {
		timeContext->frameCounter++;
        // Pour lire la frame sans updater une fois sur deux 
        if (timeContext->frameCounter <= 1) {
            if (av_read_frame(ffmpegContext->formatContext, 
                        &ffmpegContext->videoPacket) >= 0) {
                if (ffmpegContext->videoPacket.stream_index 
                        == ffmpegContext->videoStreamIndex) {
                    int ret = 1;
                    while (ret != 0 && ret != AVERROR_EOF) {
                        avcodec_send_packet(ffmpegContext->codecContext,
                                            &ffmpegContext->videoPacket);
                        ret = avcodec_receive_frame(ffmpegContext
                                    ->codecContext, ffmpegContext->frame);

                        if (ret == AVERROR(EAGAIN)) {
                                    // Pas de trame disponible, 
                                    // lire un nouveau paquet
                                    // On lit ici un nouveau paquet 
                                    // avant de continuer
                                    if (av_read_frame(ffmpegContext
                                                ->formatContext, 
                                                &ffmpegContext
                                                ->videoPacket) < 0) {
                                        // Aucun paquet disponible, 
                                        // sortir de la boucle
                                        break; 
                                    }
                                    continue; // Continue 
                                              // à la prochaine itération
                        }

                        if (ret < 0) {
                            printf("Err lors de la réceptionde la trame:"
                                   " %s\n", av_err2str(ret));
                            break;
                        }
                        else {
                            // Trame décodée avec succès,
                            // afficher ou traiter la trame
                            SDL_UpdateYUVTexture(textureContext->video_T,
                                                NULL,
                                                 ffmpegContext->frame
                                                 ->data[0],
                                                 ffmpegContext->frame
                                                 ->linesize[0],
                                                 ffmpegContext->frame
                                                 ->data[1],
                                                 ffmpegContext->frame
                                                 ->linesize[1],
                                                 ffmpegContext->frame
                                                 ->data[2], ffmpegContext
                                                 ->frame->linesize[2]);
                            SDL_RenderCopy(sdlContext->renderer,
                                    textureContext->video_T, NULL, NULL);
                            av_frame_unref(ffmpegContext->frame);
                        }
                    }
                }
                av_packet_unref(&ffmpegContext->videoPacket);
            }
        }
        else {
            // Ne lit pas la frame, mais affiche la précédente
            SDL_RenderCopy(sdlContext->renderer, 
                    textureContext->video_T, NULL, NULL);
            timeContext->frameCounter = 0;
        }
    }
}

