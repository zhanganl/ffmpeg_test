/**
* 最简单的基于FFmpeg的视频解码器（纯净版）
* Simplest FFmpeg Decoder Pure
*
* 雷霄骅 Lei Xiaohua
* leixiaohua1020@126.com
* 中国传媒大学/数字电视技术
* Communication University of China / Digital TV Technology
* http://blog.csdn.net/leixiaohua1020
*
*
* 本程序实现了视频码流(支持HEVC，H.264，MPEG2等)解码为YUV数据。
* 它仅仅使用了libavcodec（而没有使用libavformat）。
* 是最简单的FFmpeg视频解码方面的教程。
* 通过学习本例子可以了解FFmpeg的解码流程。
* This software is a simplest decoder based on FFmpeg.
* It decode bitstreams to YUV pixel data.
* It just use libavcodec (do not contains libavformat).
* Suitable for beginner of FFmpeg.
*/

#include <stdio.h>
#include "ffmpeg_encode.h"


int main(int argc, char* argv[])
{

	ffmpeg_encode ff_enc;


	int i, ret, got_output;
	FILE *fp_in;
	FILE *fp_out;
	AVFrame *pFrame;
	int y_size;
	int framecnt = 0;
	int framenum = 100;

	int out_264_len;
	uint8_t* out_264;
	out_264 = (uint8_t*)malloc(30000);

	char filename_in[] = "../ds_480x272.yuv";

#if TEST_HEVC
	AVCodecID codec_id=AV_CODEC_ID_HEVC;
	char filename_out[]="ds.hevc";
#else
	AVCodecID codec_id=AV_CODEC_ID_H264;
	char filename_out[]="ds.h264";
#endif

	pFrame = av_frame_alloc();
	if (!pFrame) {
		printf("Could not allocate video frame\n");
		return -1;
	}
	pFrame->format = ff_enc.pCodecCtx->pix_fmt;
	pFrame->width = ff_enc.pCodecCtx->width;
	pFrame->height = ff_enc.pCodecCtx->height;

	ret = av_image_alloc(pFrame->data, pFrame->linesize, ff_enc.pCodecCtx->width, ff_enc.pCodecCtx->height,
		ff_enc.pCodecCtx->pix_fmt, 16);
	if (ret < 0) {
		printf("Could not allocate raw picture buffer\n");
		return -1;
	}
	//Input raw data
	fp_in = fopen(filename_in, "rb");
	if (!fp_in) {
		printf("Could not open %s\n", filename_in);
		return -1;
	}
	//Output bitstream
	fp_out = fopen(filename_out, "ab+");
	if (!fp_out) {
		printf("Could not open %s\n", filename_out);
		return -1;
	}

	y_size = ff_enc.pCodecCtx->width * ff_enc.pCodecCtx->height;
	//Encode
	for (i = 0; i < framenum; i++) {
		//Read raw YUV data
		if (fread(pFrame->data[0], 1, y_size, fp_in) <= 0 ||		// Y
			fread(pFrame->data[1], 1, y_size / 4, fp_in) <= 0 ||	// U
			fread(pFrame->data[2], 1, y_size / 4, fp_in) <= 0){	// V
			return -1;
		}
		else if (feof(fp_in)){
			break;
		}

		pFrame->pts = i;
		/* encode the image */
		ff_enc.encode(out_264, out_264_len, pFrame);

		if (ret < 0) {
			printf("Error encoding frame\n");
			return -1;
		}

		fwrite(out_264, 1, out_264_len, fp_out);
		
	}

	fclose(fp_in);
	fclose(fp_out);
	return 0;
}

