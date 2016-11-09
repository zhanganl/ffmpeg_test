#include "ffmpeg_encode.h"

ffmpeg_encode::ffmpeg_encode()
{
	int ret;
	pCodecCtx = NULL;

	y_size = 0;
	codec_id = AV_CODEC_ID_H264;
	got_output = 0;

	avcodec_register_all();

	pCodec = avcodec_find_encoder(codec_id);
	if (!pCodec) {
		printf("Codec not found\n");
	}
	pCodecCtx = avcodec_alloc_context3(pCodec);
	if (!pCodecCtx) {
		printf("Could not allocate video codec context\n");
	}
	pCodecCtx->bit_rate = 400000;
	pCodecCtx->width = 640;
	pCodecCtx->height = 480;
	pCodecCtx->time_base.num = 1;
	pCodecCtx->time_base.den = 25;
	pCodecCtx->gop_size = 10;
	pCodecCtx->max_b_frames = 0;
	pCodecCtx->pix_fmt = AV_PIX_FMT_YUV420P;
	//pCodecCtx->has_b_frames = 0;

	if (codec_id == AV_CODEC_ID_H264)
		av_opt_set(pCodecCtx->priv_data, "preset", "slow", 0);


	if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0) {
		printf("Could not open codec\n");
	}

	//pFrame = av_frame_alloc();
	//if (!pFrame) {
	//	printf("Could not allocate video frame\n");
	//}
	//pFrame->format = pCodecCtx->pix_fmt;
	//pFrame->width = pCodecCtx->width;
	//pFrame->height = pCodecCtx->height;

	//ret = av_image_alloc(pFrame->data, pFrame->linesize, pCodecCtx->width, pCodecCtx->height,
		//pCodecCtx->pix_fmt, 16);
	//if (ret < 0) {
	//	printf("Could not allocate raw picture buffer\n");
	//}
}

ffmpeg_encode::~ffmpeg_encode()
{
	avcodec_close(pCodecCtx);
	av_free(pCodecCtx);
	//av_freep(&pFrame->data[0]);
	//av_frame_free(&pFrame);
}

int ffmpeg_encode::encode(uint8_t* src, int& src_len, AVFrame *pFrame, int &got_output)
{
		int ret;
		int i = 0;
		//if (got_output) {
		//	av_free_packet(&pkt);
		//}
		av_init_packet(&pkt);
		pkt.data = NULL;    // packet data will be allocated by the encoder
		pkt.size = 0;
		//static int number = 0;
		//pFrame->pts = number;
		/* encode the image */
		//for (i = 0; i < pFrame->width; i++)
		//{
		//	printf("pFrame :%d  ", pFrame->data[0][i]);
		//}
		ret = avcodec_encode_video2(pCodecCtx, &pkt, pFrame, &got_output);
		if (ret < 0) {
			printf("Error encoding frame\n");
			return -2;
		}
		//if (got_output){
		//for (i = 0; i < pkt.size; i++)
		//{
		//	printf("%d  ", pkt.data[i]);
		//}
		//}
		//src = pkt.data;

		//pkt.data = src;
		//pkt.size = src_len;
		//number++;
		if (got_output) {
			memcpy(src, pkt.data, pkt.size);
			src_len = pkt.size;
			printf("******************src_len :%d********************\n", src_len);
			av_free_packet(&pkt);
			return 0;
		}
	return -1;
}




