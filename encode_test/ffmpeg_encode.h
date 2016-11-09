#include <stdio.h>

#ifdef _WIN32
//Windows
extern "C"
{
#include "libavutil/opt.h"
#include "libavcodec/avcodec.h"
#include "libavutil/imgutils.h"
};
#else
//Linux...
#ifdef __cplusplus
extern "C"
{
#endif
#include <libavutil/opt.h>
#include <libavcodec/avcodec.h>
#include <libavutil/imgutils.h>
#define __STDC_CONSTANT_MACROS
#ifdef __cplusplus
};
#endif
#endif

class ffmpeg_encode
{
public:
	ffmpeg_encode();
	~ffmpeg_encode();
	int encode(uint8_t* src, int& src_len, AVFrame *pFrame, int &got_output);

public:
	AVCodec *pCodec;
	AVCodecContext *pCodecCtx;
	//AVFrame *pFrame;
	AVPacket pkt;
	AVCodecID codec_id;
	int y_size;
	int got_output;
};
