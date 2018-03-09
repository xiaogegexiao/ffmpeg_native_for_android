#include "foscam_pcm.h"

#define FOSCAM_RAW_SAMPLES 4096
int foscam_pcm_read_packet (AVFormatContext *s, AVPacket *pkt) {
//
    int packet_size, ret;

    int size = FOSCAM_RAW_SAMPLES;
    char data[4096];
    FOSDEC_DATA* fos_data = NULL;
    FoscamPCMAudioDemuxerContext *s1 = s->priv_data;

    if (av_new_packet(pkt, size) < 0)
        return AVERROR(ENOMEM);

    pkt->pos = avio_tell(s->pb);
    pkt->stream_index = 0;
    ret = ffio_read_partial(s->pb, data, size);

    if (ret < 0) {
        av_packet_unref(pkt);
        return ret;
    }

    fos_data = (FOSDEC_DATA *)data;

    if (s1->start_timestamp == 0) {
        s1->start_timestamp = fos_data->pts;
    }

    pkt->dts = av_rescale_q(fos_data->pts - s1->start_timestamp,
                            (AVRational){1, 1000}, s->streams[0]->time_base);
    pkt->camera_pts = fos_data->pts;

    //av_log (NULL, AV_LOG_ERROR, "pkt dts %lld start_timestamp %lld, fos_data pts %lld, stream timebase {%d/%d}", pkt->dts,
    //        s1->start_timestamp, fos_data->pts, s->streams[0]->time_base.num, s->streams[0]->time_base.den);
    memcpy(pkt->data, fos_data->data, fos_data->len);
    ret = fos_data->len;

    av_shrink_packet(pkt, ret);
    //av_log(NULL, AV_LOG_ERROR, "foscam_read_packet key frame %d pts %lld timebase %d/%d and dts is %lld", fos_data->isKey, fos_data->pts, s->streams[0]->time_base.num, s->streams[0]->time_base.den, pkt->dts);
    //  av_log(NULL, AV_LOG_ERROR, "foscam_read_header ret is %d fos pts %lld dts %lld", ret,
    //       fos_data->pts);
    return ret;

}

int foscam_pcm_read_header(AVFormatContext *s)
{
    FoscamPCMAudioDemuxerContext *s1 = s->priv_data;
    AVStream *st;

    st = avformat_new_stream(s, NULL);
    if (!st)
        return AVERROR(ENOMEM);


    st->codec->codec_type  = AVMEDIA_TYPE_AUDIO;
    st->codec->codec_id    = s->iformat->raw_codec_id;
    st->codec->sample_rate = s1->sample_rate;
    st->codec->channels    = s1->channels;

    st->codec->bits_per_coded_sample =
        av_get_bits_per_sample(st->codec->codec_id);

    av_assert0(st->codec->bits_per_coded_sample > 0);

    st->codec->block_align =
        st->codec->bits_per_coded_sample * st->codec->channels / 8;

    avpriv_set_pts_info(st, 64, 1, st->codec->sample_rate);
    return 0;
}
