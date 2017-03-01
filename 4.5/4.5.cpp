#include <opencv2\opencv.hpp>
using namespace cv;

#include <vector>
using namespace std;

void Lomo(Mat img);

int main()
{
	// 加载图片文件
	String imgFile = "C:\\Users\\mengf\\Pictures\\Work Pictures\\lena.jpg";
	Mat img = imread(imgFile);

	imshow("RAW", img);
	waitKey(0);
	Lomo(img);
	waitKey(0);
	return 0;
}

void Lomo(Mat img)
{
	Mat result;

	const double exponential_e = std::exp(1.0);

	// 建立一个包含256个元素的映射表
	Mat lut(1, 256, CV_8UC1);
	for (int i = 0; i < 256; i++)
	{
		float x = float(i) / 256.0;
		lut.at<uchar>(i) = cvRound(256 * (1 / (1 + pow(exponential_e, -((x - 0.5) / 0.1)))));
	}

	// 拆分图像通道，并只给红色通道应用值变换
	vector<Mat> bgr;
	split(img, bgr);
	LUT(bgr[2], lut, bgr[2]);
	merge(bgr, result);		// 合并结果

	// 创建晕暗的图像
	Mat halo(img.rows, img.cols, CV_32FC3, Scalar(0.3, 0.3, 0.3));
	// 创建圆
	circle(halo, Point(img.cols / 2, img.rows / 2), img.cols / 3, Scalar(1, 1, -1), -1);
	blur(halo, halo, Size(img.cols / 3, img.cols / 3));

	// 将结果转换成浮点型
	Mat resultf;
	result.convertTo(resultf, CV_32FC3);

	// 将结果和halo相乘
	multiply(resultf, halo, resultf);

	// 转换成8位图像
	resultf.convertTo(result, CV_8UC3);

	// 展示结果
	imshow("Lomograpy", result);
}