// 5.2.cpp -- AOI Application
#include <opencv2\opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	String img_file = "";
	Mat img = imread(img_file, 0);		// 加载待处理的图像
	if (img.data == NULL)		// 如果读取图片文件失败
	{
		cout << "Error loading image " << img_file << endl;
		return -1;
	}
	return 0;
}