// 2.6.cpp -- ��дͼ��
#include <iostream>
using namespace std;

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
using namespace cv;

int main(int argc, const char **argv)
{
	// ��ͼ��
	Mat color = imread("lena.jpg");
	Mat gray = imread("lena.jpg", 0);

	// дͼ��
	imwrite("lenaGray.jpg", gray);

	// ͨ��OpenCV������ȡ��ͬ����
	int myRow = color.cols - 1;
	int myCol = color.rows - 1;
	Vec3b pixel = color.at<Vec3b>(myRow, myCol);
	cout << "Pixel value (B,G,R): (" << int(pixel[0]) << ","
		<< int(pixel[1]) << "," << int(pixel[2]) << ")" << endl;

	// ��ʾͼ��
	imshow("Lena BGR", color);
	imshow("Lena Gray", gray);

	// �ȴ�����
	waitKey(0);
	return 0;
}