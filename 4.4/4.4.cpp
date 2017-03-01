// 4.4.cpp
#include <opencv2\opencv.hpp>
using namespace cv;

#include <vector>
using namespace std;

void equalize(Mat img);

int main()
{
	// 加载图片文件
	String imgFile = "C:\\Users\\mengf\\Pictures\\Work Pictures\\lena.jpg";
	Mat img = imread(imgFile);

	imshow("RAW", img);
	waitKey(0);
	equalize(img);
	waitKey(0);
	return 0;
}

void equalize(Mat img)
{
	Mat result;
	// BGR图像转换为YCbCr
	Mat ycrcb;
	cvtColor(img, ycrcb, COLOR_BGR2YCrCb);

	// 图像通道分离
	vector<Mat> channels;
	split(ycrcb, channels);

	// 只均衡Y通道
	equalizeHist(channels[0], channels[0]);

	// 合并结果通道
	merge(channels, ycrcb);

	// 将YCrCb转换成BGR格式
	cvtColor(ycrcb, result, COLOR_YCrCb2BGR);

	// 显示图像
	imshow("Equalized", result);
}