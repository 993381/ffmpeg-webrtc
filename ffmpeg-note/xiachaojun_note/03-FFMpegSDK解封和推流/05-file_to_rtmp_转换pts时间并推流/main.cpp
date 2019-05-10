/*******************************************************************************
**                                                                            **
**                     Jiedi(China nanjing)Ltd.                               **
**	               �������Ĳܿ����˴��������Ϊѧϰ�ο�                       **
*******************************************************************************/

/*****************************FILE INFOMATION***********************************
**
**  Project       : FFmpegSDKʵս�γ�
**  Description   : ����FFMpegSDK��ʵս�γ�
**  Contact       : xiacaojun@qq.com
**  ����   : http://blog.csdn.net/jiedichina
**  ��Ƶ�γ�
**  http://edu.csdn.net/lecturer/lecturer_detail?lecturer_id=961
**  http://edu.51cto.com/lecturer/12016059.html
**  http://study.163.com/u/xiacaojun
**  https://jiedi.ke.qq.com/
**  ����γ̺���Լ�Ⱥ��ѯ�γ�ѧϰ����
**  Ⱥ�� 132323693 fmpeg��ֱ�������γ�
**  ΢�Ź��ں�  : jiedi2007
**	ͷ����	 : �Ĳܿ�
**
*******************************************************************************/

extern "C"
{
#include "libavformat/avformat.h"
#include "libavutil/time.h"
}
#include <iostream>
using namespace std;
#pragma comment(lib,"avformat.lib")
#pragma comment(lib,"avutil.lib")
#pragma comment(lib,"avcodec.lib")

int XError(int errNum)
{
	char buf[1024] = { 0 };
	av_strerror(errNum, buf, sizeof(buf));
	cout << buf << endl;
	getchar();
	return -1;
}
int main(int argc, char *argv[])
{

	char *inUrl = "test.flv";
	char *outUrl = "rtmp://192.168.1.44/live";

	//��ʼ�����з�װ�ͽ��װ flv mp4 mov mp3
	av_register_all();

	//��ʼ�������
	avformat_network_init();

	//////////////////////////////////////////////////////////////////////////
	//������ 1 ���ļ������װ
	//�����װ������
	AVFormatContext *ictx = NULL;

	//���ļ�������ļ�ͷ
	int re = avformat_open_input(&ictx, inUrl, 0, 0);
	if (re != 0)
	{
		return XError(re);
	}
	cout << "open file " << inUrl << " Success." << endl;

	//��ȡ��Ƶ��Ƶ����Ϣ ,h264 flv
	re = avformat_find_stream_info(ictx, 0);
	if (re != 0)
	{
		return XError(re);
	}
	av_dump_format(ictx, 0, inUrl, 0);
	//////////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////////
	//����� 

	//���������������
	AVFormatContext *octx = NULL;
	re = avformat_alloc_output_context2(&octx, 0, "flv", outUrl);
	if (!octx)
	{
		return XError(re);
	}
	cout << "octx create success!" << endl;

	//���������
	//���������AVStream
	for (int i = 0; i < ictx->nb_streams; i++)
	{
		//���������
		AVStream *out = avformat_new_stream(octx, ictx->streams[i]->codec->codec);
		if (!out)
		{
			return XError(0);
		}
		//����������Ϣ,ͬ��MP4
		//re = avcodec_copy_context(out->codec, ictx->streams[i]->codec);
		re = avcodec_parameters_copy(out->codecpar, ictx->streams[i]->codecpar);
		out->codec->codec_tag = 0;
	}
	av_dump_format(octx, 0, outUrl, 1);
	//////////////////////////////////////////////////////////////////////////


	//rtmp����

	//��io
	re = avio_open(&octx->pb, outUrl, AVIO_FLAG_WRITE);
	if (!octx->pb)
	{
		return XError(re);
	}

	//д��ͷ��Ϣ
	re = avformat_write_header(octx, 0);
	if (re < 0)
	{
		return XError(re);
	}
	cout << "avformat_write_header " << re << endl;
	AVPacket pkt;
	for (;;)
	{
		re = av_read_frame(ictx, &pkt);
		if (re != 0)
		{
			break;
		}
		cout << pkt.pts << " " << flush;
		//����ת��pts dts
		AVRational itime = ictx->streams[pkt.stream_index]->time_base;
		AVRational otime = octx->streams[pkt.stream_index]->time_base;
		pkt.pts = av_rescale_q_rnd(pkt.pts, itime, otime, (AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_NEAR_INF));
		pkt.dts = av_rescale_q_rnd(pkt.pts, itime, otime, (AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_NEAR_INF));
		pkt.duration = av_rescale_q_rnd(pkt.duration, itime, otime, (AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_NEAR_INF));
		pkt.pos = -1;

		//��Ƶ֡�����ٶ�
		if (pkt.stream_index == 0)
			av_usleep(30*1000);

		re = av_interleaved_write_frame(octx, &pkt);
		if (re<0)
		{
			return XError(re);
		}
	}

	cout << "file to rtmp test" << endl;
	getchar();
	return 0;
}