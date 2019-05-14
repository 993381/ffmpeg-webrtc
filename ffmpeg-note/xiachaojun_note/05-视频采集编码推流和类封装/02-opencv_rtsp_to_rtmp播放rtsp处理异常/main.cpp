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

#include <opencv2/highgui.hpp>
#include <iostream>
#pragma comment(lib,"opencv_world320.lib")
using namespace std;
using namespace cv;
int main(int argc, char *argv[])
{
	//���������rtsp url
	char *inUrl = "rtsp://test:test123456@192.168.1.64";
	VideoCapture cam;
	namedWindow("video");

	cam.open(inUrl);
	try
	{
		if (!cam.isOpened())
		{
			throw exception("cam open failed!");
		}
		cout << inUrl << " cam open success" << endl;
		
		Mat frame;
		for (;;)
		{
			///��ȡrtsp��Ƶ֡��������Ƶ֡
			if (!cam.grab())
			{
				continue;
			}
			///yuvת��Ϊrgb
			if (!cam.retrieve(frame))
			{
				continue;
			}
			imshow("video", frame);
			waitKey(1);
		}
	}
	catch (exception &ex)
	{
		if (cam.isOpened())
			cam.release();
		cerr << ex.what() << endl;
	}
	getchar();

	return 0;
}