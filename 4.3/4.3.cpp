// 4.3.cpp -- 绘制直方图
#include <iostream>
using namespace std;

#include <opencv2\opencv.hpp>
using namespace cv;

// 加载图片文件
String imgFile = "C:\\Users\\mengf\\Pictures\\Work Pictures\\lena.jpg";
Mat img = imread(imgFile);

void showHiston(Mat img);

int main()
{
	// 加载图片文件
	String imgFile = "C:\\Users\\mengf\\Pictures\\Work Pictures\\lena.jpg";
	Mat img = imread(imgFile);

	imshow("RAW", img);
	showHiston(img);
	waitKey(0);
	return 0;
}

void showHiston(Mat img)
{
	// 把图像分割成3个通道BRG
	vector<Mat> bgr;
	split(img, bgr);

	// 创建有256个子区间的直方图
	// 值的可能值数量为[0..255]
	int numbins = 256;

	// 设置(B,G,R),最后一个值不包含
	float range[] = { 0, 256 };
	const float *histRange = { range };

	Mat b_hist, g_hist, r_hist;

	calcHist(&bgr[0], 1, 0, Mat(), b_hist, 1, &numbins, &histRange);
	calcHist(&bgr[1], 1, 0, Mat(), g_hist, 1, &numbins, &histRange);
	calcHist(&bgr[2], 1, 0, Mat(), r_hist, 1, &numbins, &histRange);

	// 绘制直方图
	// 将为每个图像通道绘线
	int width = 512;
	int height = 300;
	// 以灰色为基地创建图像
	Mat histImage(height, width, CV_8UC3, Scalar(20, 20, 20));

	// 从0到图像的高度归一化直方图
	normalize(b_hist, b_hist, 0, height, NORM_MINMAX);
	normalize(g_hist, g_hist, 0, height, NORM_MINMAX);
	normalize(r_hist, r_hist, 0, height, NORM_MINMAX);

	int binStep = cvRound(float(width) / float(numbins));
	for (int i = 1; i < numbins; i++)
	{
		line(histImage,
			Point(binStep * (i - 1), height - cvRound(b_hist.at<float>(i - 1))),
			Point(binStep * (i), height - cvRound(b_hist.at<float>(i))),
			Scalar(255, 0, 0));
		line(histImage,
			Point(binStep * (i - 1), height - cvRound(g_hist.at<float>(i - 1))),
			Point(binStep * (i), height - cvRound(g_hist.at<float>(i))),
			Scalar(0, 255, 0));
		line(histImage,
			Point(binStep * (i - 1), height - cvRound(r_hist.at<float>(i - 1))),
			Point(binStep * (i), height - cvRound(r_hist.at<float>(i))),
			Scalar(0, 0, 255));
	}
	imshow("Histongram", histImage);
}

