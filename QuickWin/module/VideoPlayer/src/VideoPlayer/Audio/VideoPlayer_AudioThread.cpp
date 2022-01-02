/**
 * Ҷ����
 * QQȺ121376426
 * http://blog.yundiantech.com/
 */

#include "VideoPlayer/VideoPlayer.h"

#include "PcmVolumeControl.h"

#include <stdio.h>

void VideoPlayer::sdlAudioCallBackFunc(void *userdata, Uint8 *stream, int len)
{
    VideoPlayer *player = (VideoPlayer*)userdata;
    player->sdlAudioCallBack(stream, len);
}

void VideoPlayer::sdlAudioCallBack(Uint8 *stream, int len)
{
    int len1, audio_data_size;

    /*   len����SDL�����SDL�������Ĵ�С������������δ�������Ǿ�һֱ����������� */
    while (len > 0)
    {
        /*  audio_buf_index �� audio_buf_size ��ʾ�����Լ��������ý�����������ݵĻ�������*/
        /*   ��Щ���ݴ�copy��SDL�������� ��audio_buf_index >= audio_buf_size��ʱ����ζ����*/
        /*   �ǵĻ���Ϊ�գ�û�����ݿɹ�copy����ʱ����Ҫ����audio_decode_frame���������
         /*   ��������� */
        if (audio_buf_index >= audio_buf_size)
        {
            audio_data_size = decodeAudioFrame();

            /* audio_data_size < 0 ��ʾû�ܽ�������ݣ�����Ĭ�ϲ��ž��� */
            if (audio_data_size <= 0)
            {
                /* silence */
                audio_buf_size = 1024;
                /* ���㣬���� */
                memset(audio_buf, 0, audio_buf_size);
            }
            else
            {
                audio_buf_size = audio_data_size;
            }
            audio_buf_index = 0;
        }
        /*  �鿴stream���ÿռ䣬����һ��copy�������ݣ�ʣ�µ��´μ���copy */
        len1 = audio_buf_size - audio_buf_index;

        if (len1 > len)
        {
            len1 = len;
        }

        if (audio_buf == NULL) return;

        if (mIsMute || mIsNeedPause) //���� ���� ������ͣ��ʱ����ת��
        {
            memset(audio_buf + audio_buf_index, 0, len1);
        }
        else
        {
            PcmVolumeControl::RaiseVolume((char*)audio_buf + audio_buf_index, len1, 1, mVolume);
        }

        memcpy(stream, (uint8_t *)audio_buf + audio_buf_index, len1);

//        SDL_memset(stream, 0x0, len);// make sure this is silence.
//        SDL_MixAudio(stream, (uint8_t *) audio_buf + audio_buf_index, len1, SDL_MIX_MAXVOLUME);

//        SDL_MixAudio(stream, (uint8_t * )is->audio_buf + is->audio_buf_index, len1, 50);
//        SDL_MixAudioFormat(stream, (uint8_t * )is->audio_buf + is->audio_buf_index, AUDIO_S16SYS, len1, 50);

        len -= len1;
        stream += len1;
        audio_buf_index += len1;

    }

}

int VideoPlayer::decodeAudioFrame(bool isBlock)
{
    int audioBufferSize = 0;

    while(1)
    {
        if (mIsQuit)
        {
            mIsAudioThreadFinished = true;
            clearAudioQuene(); //��ն���
            break;
        }

        if (mIsPause == true) //�ж���ͣ
        {
            break;
        }

        mConditon_Audio->Lock();

        if (mAudioPacktList.size() <= 0)
        {
            if (isBlock)
            {
                mConditon_Audio->Wait();
            }
            else
            {
                mConditon_Audio->Unlock();
                break;
            }
        }

        AVPacket packet = mAudioPacktList.front();
        mAudioPacktList.pop_front();

        mConditon_Audio->Unlock();

        AVPacket *pkt = &packet;

        /* if update, update the audio clock w/pts */
        if (pkt->pts != AV_NOPTS_VALUE)
        {
            audio_clock = av_q2d(mAudioStream->time_base) * pkt->pts;
        }

        //�յ�������� ˵���ո�ִ�й���ת ������Ҫ�ѽ����������� ���һ��
        if(strcmp((char*)pkt->data,FLUSH_DATA) == 0)
        {
            avcodec_flush_buffers(mAudioStream->codec);
            av_packet_unref(pkt);
            continue;
        }

        if (seek_flag_audio)
        {
            //��������ת �������ؼ�֡��Ŀ��ʱ����⼸֡
           if (audio_clock < seek_time)
           {
               continue;
           }
           else
           {
               seek_flag_audio = 0;
           }
        }

        //����AVPacket->AVFrame
        int got_frame = 0;
        int size = avcodec_decode_audio4(aCodecCtx, aFrame, &got_frame, &packet);

//�����ز���֮ǰ��һ�����������ݷ���
//size_t unpadded_linesize = aFrame->nb_samples * av_get_bytes_per_sample((AVSampleFormat) aFrame->format);
//static FILE * fp = fopen("out.pcm", "wb");
//fwrite(aFrame->extended_data[0], 1, unpadded_linesize, fp);

        av_packet_unref(&packet);

        if (got_frame)
        {
            /// ffmpeg����֮��õ�����Ƶ���ݲ���SDL��Ҫ�ģ�
            /// ���������Ҫ�ز�����44100 ˫���� AV_SAMPLE_FMT_S16
            if (aFrame_ReSample == NULL)
            {
                aFrame_ReSample = av_frame_alloc();
            }

            if (aFrame_ReSample->nb_samples != aFrame->nb_samples)
            {
                aFrame_ReSample->nb_samples = av_rescale_rnd(swr_get_delay(swrCtx, out_sample_rate) + aFrame->nb_samples,
                            out_sample_rate, in_sample_rate, AV_ROUND_UP);

                av_samples_fill_arrays(aFrame_ReSample->data, aFrame_ReSample->linesize, audio_buf, audio_tgt_channels, aFrame_ReSample->nb_samples, out_sample_fmt, 0);

            }

            int len2 = swr_convert(swrCtx, aFrame_ReSample->data, aFrame_ReSample->nb_samples, (const uint8_t**)aFrame->data, aFrame->nb_samples);
            int resampled_data_size = len2 * audio_tgt_channels * av_get_bytes_per_sample(out_sample_fmt);

            audioBufferSize = resampled_data_size;
            break;
        }
    }

    return audioBufferSize;
}
