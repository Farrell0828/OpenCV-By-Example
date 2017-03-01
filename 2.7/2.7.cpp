// 2.7.cpp -- 读取视频和摄像头

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

// OpenCV头文件
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
using namespace cv;

// OpenCV命令行解析函数
// 命令行解析器接受按键
const char *keys =
{
	"{help h usage ? | | print this message}"
	"{@video | | Video file, if not defined try to use webcamera}"
};

int main(int argc, const char **argv)
{
	CommandLineParser parser(argc, argv, keys);
	parser.about("Chapter 2. v1.0.0");

	// 如果需要，显示帮助文档
	if (parser.has("help"))
	{
		parser.printMessage();
		return 0;
	}
	String videoFile = parser.get<String>(0);

	// 分析params的变量，检查params是否正确
	if (!parser.check())
	{
		parser.printErrors();
		return 0;
	}

	VideoCapture cap;		// 打开默认相机
	if (videoFile != "")
		cap.open(videoFile);
	else
		cap.open(0);
	if (!cap.isOpened())	// 检查是否成功了
		return -1;

	namedWindow("Video", 1);
	while (true)
	{
		Mat frame;
		cap >> frame;		// 获取摄像机的帧
		imshow("Video", frame);
		if (waitKey(30) >= 0) break;
	}
	// 释放摄像机或视频cap
	cap.release();

	return 0;
}