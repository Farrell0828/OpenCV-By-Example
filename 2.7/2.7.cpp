// 2.7.cpp -- ��ȡ��Ƶ������ͷ

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

// OpenCVͷ�ļ�
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
using namespace cv;

// OpenCV�����н�������
// �����н��������ܰ���
const char *keys =
{
	"{help h usage ? | | print this message}"
	"{@video | | Video file, if not defined try to use webcamera}"
};

int main(int argc, const char **argv)
{
	CommandLineParser parser(argc, argv, keys);
	parser.about("Chapter 2. v1.0.0");

	// �����Ҫ����ʾ�����ĵ�
	if (parser.has("help"))
	{
		parser.printMessage();
		return 0;
	}
	String videoFile = parser.get<String>(0);

	// ����params�ı��������params�Ƿ���ȷ
	if (!parser.check())
	{
		parser.printErrors();
		return 0;
	}

	VideoCapture cap;		// ��Ĭ�����
	if (videoFile != "")
		cap.open(videoFile);
	else
		cap.open(0);
	if (!cap.isOpened())	// ����Ƿ�ɹ���
		return -1;

	namedWindow("Video", 1);
	while (true)
	{
		Mat frame;
		cap >> frame;		// ��ȡ�������֡
		imshow("Video", frame);
		if (waitKey(30) >= 0) break;
	}
	// �ͷ����������Ƶcap
	cap.release();

	return 0;
}