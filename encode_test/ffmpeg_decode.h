#include <stdio.h>

#ifdef _WIN32
//Windows
extern "C"
{
#include "libavcodec/avcodec.h"
};
#else
//Linux...
#ifdef __cplusplus
extern "C"
{
#endif
#include <libavcodec/avcodec.h>
#ifdef __cplusplus
};
#endif
#endif

class ffmpeg_decode
{
public:
	ffmpeg_decode();
	~ffmpeg_decode();
	int decode(uint8_t* src, int src_len, AVFrame *pFrame);

private:
	AVCodec *pCodec;
	AVCodecContext *pCodecCtx;
	AVCodecParserContext *pCodecParserCtx;
	//AVFrame	*pFrame;
	AVPacket packet;
	int got_picture;
	AVCodecID codec_id;
};
