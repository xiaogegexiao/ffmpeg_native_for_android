
#ifndef AVFORMAT_FOSCAM_PCM_H
#define AVFORMAT_FOSCAM_PCM_H

#include "avformat.h"
#include "pcm.h"
#include "foscam/fossdk.h"
#include "avio_internal.h"
#include "internal.h"
#include "libavutil/log.h"
#include "libavutil/opt.h"
#include "libavutil/avassert.h"

int foscam_pcm_read_packet (AVFormatContext *s, AVPacket *pkt);
int foscam_pcm_read_header(AVFormatContext *s);

typedef struct FoscamPCMAudioDemuxerContext {
    AVClass *class;
    int sample_rate;
    int channels;
    int64_t start_timestamp;
} FoscamPCMAudioDemuxerContext;

static const AVOption foscam_pcm_options[] = {
    { "sample_rate", "", offsetof(FoscamPCMAudioDemuxerContext, sample_rate), AV_OPT_TYPE_INT, {.i64 = 8000}, 0, INT_MAX, AV_OPT_FLAG_DECODING_PARAM },
    { "channels",    "", offsetof(FoscamPCMAudioDemuxerContext, channels),    AV_OPT_TYPE_INT, {.i64 = 1}, 0, INT_MAX, AV_OPT_FLAG_DECODING_PARAM },
    { "start_timestamp", "", offsetof(FoscamPCMAudioDemuxerContext, start_timestamp), AV_OPT_TYPE_INT64, {.i64 = 0}, INT64_MIN, INT64_MAX, 0},
    { NULL },
};

static const AVClass foscam_s16le_demuxer_class = {
    .class_name = "foscam pcm demuxer",
    .item_name  = av_default_item_name,
    .option     = foscam_pcm_options,
    .version    = LIBAVUTIL_VERSION_INT,
};

AVInputFormat ff_foscam_s16le_demuxer = {
    .name           = "foscam_s16le",
    .long_name      = NULL_IF_CONFIG_SMALL("foscam s16le raw pcm"),
    .priv_data_size = sizeof(FoscamPCMAudioDemuxerContext),
    .read_header    = foscam_pcm_read_header,
    .read_packet    = foscam_pcm_read_packet,
    .read_seek      = ff_pcm_read_seek,
    .flags          = AVFMT_GENERIC_INDEX,
    .extensions     = "foscam",
    .raw_codec_id   = AV_CODEC_ID_PCM_S16LE,
    .priv_class     = &foscam_s16le_demuxer_class,
};

#endif
