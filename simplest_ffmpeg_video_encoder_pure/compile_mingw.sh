#! /bin/sh
#��򵥵Ļ���FFmpeg����Ƶ�������������棩 ----MinGW�����б���
#Simplest FFmpeg Video Encoder Pure ----Compile in MinGW 
#
#������ Lei Xiaohua
#leixiaohua1020@126.com
#�й���ý��ѧ/���ֵ��Ӽ���
#Communication University of China / Digital TV Technology
#http://blog.csdn.net/leixiaohua1020
#
#compile
g++ simplest_ffmpeg_video_encoder_pure.cpp -g -o simplest_ffmpeg_video_encoder_pure.exe \
-I /usr/local/include -L /usr/local/lib \
-lavcodec -lavutil