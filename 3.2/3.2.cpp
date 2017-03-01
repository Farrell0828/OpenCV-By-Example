// 3.2.cpp -- 基本图形用户界面

#include <iostream>
#include <string>
//#include <sstream>
using namespace std;

// OpenCV头文件
#include "opencv2\core.hpp"
#include <opencv2\highgui.hpp>
using namespace cv;

// const int CV_GUI_NORMAL = 0x10;

int main()
{
	// 读取图像
	Mat lena = imread("C:\\Users\\mengf\\Pictures\\Work Pictures\\lena.jpg");
	Mat photo = imread("C:\\Users\\mengf\\Pictures\\Work Pictures\\photo.jpg");

	// 创建窗口
	namedWindow("Lena", CV_GUI_NORMAL);
	namedWindow("Photo", WINDOW_AUTOSIZE);

	// 移动窗口
	moveWindow("Lena", 10, 10);
	moveWindow("Photo", 520, 10);

	// 展示图像
	imshow("Lena", lena);
	imshow("Photo", photo);

	// 调整窗口大小，仅当非自用使用模式时
	resizeWindow("Lena", 512, 512);
	resizeWindow("Photo", 512, 512);

	// 等待有按键按下
	waitKey(0);

	// 销毁窗口
	destroyWindow("Lena");
	destroyWindow("Photo");

	// 创建10个新窗口
	for (int i = 0; i < 10; ++i)
	{
		ostringstream ss;
		ss << "Photo " << i;
		namedWindow(ss.str());
		moveWindow(ss.str(), 20 * i, 20 * i);
		imshow(ss.str(), photo);
	}

	waitKey(0);
	// 销毁所有窗口
	destroyAllWindows();
	return 0;
}