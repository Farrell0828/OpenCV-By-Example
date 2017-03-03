// 5.2.cpp -- AOI Application + 图像预处理部分
#include <opencv2\opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// 图片所在文件夹路径
const String file_path = "C:\\Users\\mengf\\Pictures\\Test Image\\";

Mat RemoveLight(Mat img, Mat pattern, int method);
Mat CalculateLightPattern(Mat img);
void ConnectedComponents(Mat img);

int main()
{
	String img_file = file_path + "pattern1.jpg";
	Mat img = imread(img_file, 0);		// 加载待处理的图像
	if (img.data == NULL)				// 如果读取图片文件失败
	{
		cout << "Error loading image " << img_file << endl;
		return -1;
	}
	imshow("原图", img);					// 展示原图

	Mat img_spnoise;					// 去除椒盐噪声后的图像
	medianBlur(img, img_spnoise, 5);	// 中值滤波
	imshow("中值滤波后的图", img_spnoise);	// 展示中值滤波后的图像

	Mat img_gnoise;						// 去除高斯噪声后的图像
	GaussianBlur(img, img_gnoise, Size(3, 3), 1.0);		// 高斯滤波
	imshow("高斯滤波后的图", img_gnoise);	// 展示高斯滤波后的图像

	waitKey();
	destroyAllWindows();

	imshow("原图", img);					// 展示原图
	String pattern_img_file = file_path + "pattern2.jpg";
	Mat pattern = imread(pattern_img_file, 0);
	if (pattern.data == NULL)			// 如果读取图片文件失败
	{
		cout << "Error loading image " << pattern_img_file << endl;
		return -1;
	}
	imshow("背景图", pattern);			// 展示背景图
	Mat removed0 = RemoveLight(img, pattern, 0);		// 用差分方法
	Mat removed1 = RemoveLight(img, pattern, 1);		// 用除法
	imshow("差分后", removed0);
	imshow("除法后", removed1);

	waitKey();
	destroyAllWindows();

	imshow("原图", img);					// 展示原图
	Mat pattern_basic = CalculateLightPattern(img);
	imshow("背景图", pattern_basic);		// 展示背景图
	Mat removed0_basic = RemoveLight(img, pattern_basic, 0);	// 用差分方法
	Mat removed1_basic = RemoveLight(img, pattern_basic, 1);	// 用除法
	imshow("差分后", removed0_basic);
	imshow("除法后", removed1_basic);

	waitKey();
	destroyAllWindows();

	// 为分割图像，先二值化
	Mat img_thr;
	// if (method_light != 2)
	{
		threshold(removed0, img_thr, 30, 255, THRESH_BINARY);
	}
	// else
	{
		threshold(removed0, img_thr, 140, 255, THRESH_BINARY_INV);
	}

	return 0;
}

Mat RemoveLight(Mat img, Mat pattern, int method)
{
	Mat aux;
	if (method == 1)		// 如果方法是归一化，即除法
	{
		// 相除需要将图像更改为32位浮点型
		Mat img32, pattern32;
		img.convertTo(img32, CV_32F);
		pattern.convertTo(pattern32, CV_32F);

		aux = 1 - (img32 / pattern32);	// 图像除以模式
		aux = aux * 255;				// 对其进行缩放以转换成8位格式
		aux.convertTo(aux, CV_8U);		// 转换成8位格式
	}
	else
	{
		aux = pattern - img;			// 模式减去图像
	}
	return aux;
}

Mat CalculateLightPattern(Mat img)
{
	Mat pattern;
	// 用基本和有效的方法来计算图像光纹
	blur(img, pattern, Size(img.cols / 3, img.cols / 3));
	return pattern;
}

void ConnectedComponents(Mat img)
{
	Mat labels;
	int num_objects = connectedComponents(img, labels);
	if (num_objects < 2)
	{
		cout << "No objects detected" << endl;
		return;
	}
	else
	{
		cout << "Number of objects detected: " << num_objects - 1 << endl;
	}
	Mat output = Mat::zeros(img.rows, img.cols, CV_8UC3);
	RNG rng(0xFFFFFFFF);
	for (int i = 1; i < num_objects; i++)
	{
		Mat mask = (labels == i);
		// output.setTo(randomColor(rng), mask);
	}
	imshow("Result", output);
}