
#ifndef AVFORMAT_FOSCAMDEC_H
#define AVFORMAT_FOSCAMDEC_H

#include "avformat.h"
#include "libavutil/log.h"
#include "libavutil/opt.h"

int foscam_read_packet(AVFormatContext *s, AVPacket *pkt);
int foscam_read_header(AVFormatContext *s);

typedef struct FFFoscamVideoDemuxerContext {
    const AVClass *class;
    char *video_size;
    char *pixel_format;
    AVRational framerate;
    int64_t start_timestamp;
} FFFoscamVideoDemuxerContext;

#define OFFSET(x) offsetof(FFFoscamVideoDemuxerContext, x)
const AVOption ff_foscam_options[] = {
    { "framerate", "", OFFSET(framerate), AV_OPT_TYPE_VIDEO_RATE, {.str = "25"}, 0, 0, AV_OPT_FLAG_DECODING_PARAM},
    {"start_timestamp", "", OFFSET(start_timestamp), AV_OPT_TYPE_INT64, {.i64=0}, INT64_MIN, INT64_MAX, 0},
    { NULL },
};

static const AVClass foscam_demuxer_class = {
    .class_name = "foscam demuxer",
    .item_name  = av_default_item_name,
    .option     = ff_foscam_options,
    .version    = LIBAVUTIL_VERSION_INT,
};

AVInputFormat ff_foscam_demuxer = {
  .name            = "foscam",
  .long_name       = "foscam demuxer",
  .read_header     = foscam_read_header,
  .read_packet     = foscam_read_packet,
  .extensions      = "foscam",
  .flags           = AVFMT_GENERIC_INDEX,
  .priv_data_size  = sizeof(FFFoscamVideoDemuxerContext),
  .priv_class      = &foscam_demuxer_class,
};

#endif //AVFORMAT_FOSCAMDEC_H
