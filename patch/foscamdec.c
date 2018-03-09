#include "internal.h"
#include "avformat.h"
#include "foscamdec.h"
#include "avio_internal.h"
#include "foscam/fossdk.h"

#define RAW_PACKET_SIZE 1024*512

int foscam_read_packet(AVFormatContext *s, AVPacket *pkt)
{

    int packet_size, ret, width, height;
    FFFoscamVideoDemuxerContext *s1 = s->priv_data;

    int size = RAW_PACKET_SIZE;
    char data[1024*502];
    FOSDEC_DATA* fos_data = NULL;

    if (av_new_packet(pkt, size) < 0) {
        av_log(NULL, AV_LOG_ERROR, "av_new_packet error");
        return AVERROR(ENOMEM);
    }

    pkt->pos = avio_tell(s->pb);
    pkt->stream_index = 0;
    ret = ffio_read_partial(s->pb, data, size);

    if (ret < 0) {
        av_log(NULL, AV_LOG_ERROR, "ffio_read_partial error");
        av_packet_unref(pkt);
        return ret;
    }

    fos_data = (FOSDEC_DATA *)data;

    if (s1->start_timestamp == 0) {
        s1->start_timestamp = fos_data->pts;
    }
    //av_log(NULL, AV_LOG_ERROR, "get start timestamp %lld, pts is %lld, diff %lld", s1->start_timestamp, fos_data->pts, fos_data->pts - s1->start_timestamp);
    pkt->dts = av_rescale_q(fos_data->pts - s1->start_timestamp,
                            (AVRational){1, 1000}, s->streams[0]->time_base);
    pkt->camera_pts = fos_data->pts;

    memcpy(pkt->data, fos_data->data, fos_data->len);
    ret = fos_data->len;

    av_shrink_packet(pkt, ret);
    //av_log(NULL, AV_LOG_ERROR, "foscamdec packet camera pts %lld", pkt->camera_pts);
    //  av_log(NULL, AV_LOG_ERROR, "foscam_read_header ret is %d fos pts %lld dts %lld", ret,
    //       fos_data->pts);
    return ret;
}

int foscam_read_header(AVFormatContext *s)
{
  //av_log(NULL, AV_LOG_ERROR, "foscam_read_header ");
    AVStream *st;
    FFFoscamVideoDemuxerContext *s1 = s->priv_data;
    int ret = 0;

    st = avformat_new_stream(s, NULL);
    if (!st) {
        ret = AVERROR(ENOMEM);
        goto fail;
    }

    st->codec->codec_type = AVMEDIA_TYPE_VIDEO;
    st->codec->codec_id = AV_CODEC_ID_H264;
    st->need_parsing = AVSTREAM_PARSE_FULL_RAW;
    //TODO: set frame rate here
    st->codec->framerate = s1->framerate;
    st->codec->time_base = av_inv_q(s1->framerate);
    av_log(NULL, AV_LOG_ERROR, "foscam_read_header get framerate is %d", s1->framerate);

    //avpriv_set_pts_info(st, 64, 1, 1200000);

fail:
    return ret;
}
