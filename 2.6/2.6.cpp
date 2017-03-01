// 2.6.cpp -- 读写图像
#include <iostream>
using namespace std;

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
using namespace cv;

int main(int argc, const char **argv)
{
	// 读图像
	Mat color = imread("lena.jpg");
	Mat gray = imread("lena.jpg", 0);

	// 写图像
	imwrite("lenaGray.jpg", gray);

	// 通过OpenCV函数获取相同像素
	int myRow = color.cols - 1;
	int myCol = color.rows - 1;
	Vec3b pixel = color.at<Vec3b>(myRow, myCol);
	cout << "Pixel value (B,G,R): (" << int(pixel[0]) << ","
		<< int(pixel[1]) << "," << int(pixel[2]) << ")" << endl;

	// 显示图像
	imshow("Lena BGR", color);
	imshow("Lena Gray", gray);

	// 等待按键
	waitKey(0);
	return 0;
}