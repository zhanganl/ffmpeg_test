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
gcc main.cpp ffmpeg_encode.cpp  -o encode \
-I /home/zhanganlong/ffmpeg_test/encode_test -L /lib64 -lavcodec -lavutil  -lstdc++
