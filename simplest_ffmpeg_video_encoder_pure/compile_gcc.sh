#! /bin/sh
#��򵥵Ļ���FFmpeg����Ƶ�������������棩----�����б���
#Simplest FFmpeg Video Encoder Pure----Compile in Shell 
#
#������ Lei Xiaohua
#leixiaohua1020@126.com
#�й���ý��ѧ/���ֵ��Ӽ���
#Communication University of China / Digital TV Technology
#http://blog.csdn.net/leixiaohua1020
#
#compile
gcc simplest_ffmpeg_video_encoder_pure.cpp -o simplest_ffmpeg_video_encoder_pure.out \
-I /home/zhanganlong/ffmpeg_test/simplest_ffmpeg_video_encoder_pure/include -L /lib64 -lavcodec -lavutil  -lstdc++
