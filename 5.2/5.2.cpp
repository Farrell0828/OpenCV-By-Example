// 5.2.cpp -- AOI Application
#include <opencv2\opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	String img_file = "";
	Mat img = imread(img_file, 0);		// ���ش������ͼ��
	if (img.data == NULL)		// �����ȡͼƬ�ļ�ʧ��
	{
		cout << "Error loading image " << img_file << endl;
		return -1;
	}
	return 0;
}