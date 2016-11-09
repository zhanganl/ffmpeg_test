#include "ffmpeg_decode.h"

ffmpeg_decode::ffmpeg_decode()
{
	pCodecCtx = NULL;
	pCodecParserCtx = NULL;
	codec_id = AV_CODEC_ID_H264;

	//av_log_set_level(AV_LOG_DEBUG);

	avcodec_register_all();

	pCodec = avcodec_find_decoder(codec_id);
	if (!pCodec) {
		printf("Codec not found\n");
	}
	pCodecCtx = avcodec_alloc_context3(pCodec);
	if (!pCodecCtx){
		printf("Could not allocate video codec context\n");
	}

	pCodecParserCtx = av_parser_init(codec_id);
	if (!pCodecParserCtx){
		printf("Could not allocate video parser context\n");
	}

	//if(pCodec->capabilities&CODEC_CAP_TRUNCATED)
	//    pCodecCtx->flags|= CODEC_FLAG_TRUNCATED; 

	if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0) {
		printf("Could not open codec\n");
	}

	//pFrame = av_frame_alloc();
	av_init_packet(&packet);
}
ffmpeg_decode::~ffmpeg_decode()
{
	av_parser_close(pCodecParserCtx);

	//av_frame_free(&pFrame);
	avcodec_close(pCodecCtx);
	av_free(pCodecCtx);
}

int ffmpeg_decode::decode(uint8_t* src, int src_len, AVFrame *pFrame)
{
	int ret;
	int len = av_parser_parse2(
		pCodecParserCtx, pCodecCtx,
		&packet.data, &packet.size,
		src, src_len,
		AV_NOPTS_VALUE, AV_NOPTS_VALUE, AV_NOPTS_VALUE);
	if (packet.size == 0)
		return -1;
	ret = avcodec_decode_video2(pCodecCtx, pFrame, &got_picture, &packet);

	if (ret < 0) {
			printf("Decode Error.\n");
			return ret;
	}
	return 0;
}