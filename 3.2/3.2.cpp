// 3.2.cpp -- ����ͼ���û�����

#include <iostream>
#include <string>
//#include <sstream>
using namespace std;

// OpenCVͷ�ļ�
#include "opencv2\core.hpp"
#include <opencv2\highgui.hpp>
using namespace cv;

// const int CV_GUI_NORMAL = 0x10;

int main()
{
	// ��ȡͼ��
	Mat lena = imread("C:\\Users\\mengf\\Pictures\\Work Pictures\\lena.jpg");
	Mat photo = imread("C:\\Users\\mengf\\Pictures\\Work Pictures\\photo.jpg");

	// ��������
	namedWindow("Lena", CV_GUI_NORMAL);
	namedWindow("Photo", WINDOW_AUTOSIZE);

	// �ƶ�����
	moveWindow("Lena", 10, 10);
	moveWindow("Photo", 520, 10);

	// չʾͼ��
	imshow("Lena", lena);
	imshow("Photo", photo);

	// �������ڴ�С������������ʹ��ģʽʱ
	resizeWindow("Lena", 512, 512);
	resizeWindow("Photo", 512, 512);

	// �ȴ��а�������
	waitKey(0);

	// ���ٴ���
	destroyWindow("Lena");
	destroyWindow("Photo");

	// ����10���´���
	for (int i = 0; i < 10; ++i)
	{
		ostringstream ss;
		ss << "Photo " << i;
		namedWindow(ss.str());
		moveWindow(ss.str(), 20 * i, 20 * i);
		imshow(ss.str(), photo);
	}

	waitKey(0);
	// �������д���
	destroyAllWindows();
	return 0;
}