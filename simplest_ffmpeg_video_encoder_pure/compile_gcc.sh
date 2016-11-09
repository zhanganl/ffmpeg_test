#! /bin/sh
#最简单的基于FFmpeg的视频编码器（纯净版）----命令行编译
#Simplest FFmpeg Video Encoder Pure----Compile in Shell 
#
#雷霄骅 Lei Xiaohua
#leixiaohua1020@126.com
#中国传媒大学/数字电视技术
#Communication University of China / Digital TV Technology
#http://blog.csdn.net/leixiaohua1020
#
#compile
gcc simplest_ffmpeg_video_encoder_pure.cpp -o simplest_ffmpeg_video_encoder_pure.out \
-I /home/zhanganlong/ffmpeg_test/simplest_ffmpeg_video_encoder_pure/include -L /lib64 -lavcodec -lavutil  -lstdc++
