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

	//if(cam.open(inUrl))
	if (cam.open(0))
	{
		cout << "open camera success!" << endl;
	}
	else
	{
		cout << "open camera failed!" << endl;

		waitKey(1);
		return -1;
	}
	Mat frame;
	for (;;)
	{
		cam.read(frame);
		imshow("video", frame);
		waitKey(1);
	}

	return 0;
}