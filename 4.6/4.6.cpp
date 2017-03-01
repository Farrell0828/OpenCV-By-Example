#include <opencv2\opencv.hpp>
using namespace cv;

#include <vector>
using namespace std;

void Cartoon(Mat img);

int main()
{

	// 加载图片文件
	String imgFile = "C:\\Users\\mengf\\Pictures\\Work Pictures\\lena.jpg";
	//String imgFile = "C:\\Users\\mengf\\Pictures\\Test Image\\piston.jpg";

	Mat img = imread(imgFile);
	//resize(img, img, img.size() / 5);

	imshow("RAW", img);
	waitKey(0);
	Cartoon(img);
	waitKey(0);
	return 0;
}

void Cartoon(Mat img)
{
	// 应用中值滤波去除可能的噪声
	Mat imgMedian;
	medianBlur(img, imgMedian, 7);
	imshow("Median", imgMedian);
	waitKey(0);

	// 用Canny检测边缘
	Mat imgCanny;
	Canny(imgMedian, imgCanny, 50, 150);
	imshow("Canny", imgCanny);
	waitKey(0);

	// 边缘膨胀
	Mat kernel = getStructuringElement(MORPH_RECT, Size(2, 2));
	dilate(imgCanny, imgCanny, kernel);
	imshow("Canny", imgCanny);
	waitKey(0);

	// 边缘值缩放到1，并将值翻转
	imgCanny = imgCanny / 255;
	imgCanny = 1 - imgCanny;
	imshow("Canny", imgCanny);
	waitKey(0);

	// 使用浮点值以便允许在0和1之间相乘
	Mat imgCannyf;
	imgCanny.convertTo(imgCannyf, CV_32FC3);
	imshow("Cannyf", imgCannyf);
	waitKey(0);

	// 模糊边缘来实现平滑效果
	blur(imgCannyf, imgCannyf, Size(5, 5));
	imshow("Cannyf", imgCannyf);
	waitKey(0);

	// 应用双边滤波器，实现色彩均匀化
	Mat imgBF;
	bilateralFilter(img, imgBF, 9, 150.0, 150.0);
	imshow("BF", imgBF);
	waitKey(0);

	// 截断颜色
	Mat result = imgBF / 25;
	result = result * 25;
	imshow("Result", result);
	waitKey(0);

	// 为边缘创建3个通道
	Mat imgCanny3c;
	Mat cannyChannels[] = { imgCannyf, imgCannyf, imgCannyf };
	merge(cannyChannels, 3, imgCanny3c);

	// 将结果转化为浮点型
	Mat resultf;
	result.convertTo(resultf, CV_32FC3);
	imshow("Resultf", resultf);
	waitKey(0);

	// 颜色和边缘矩阵相乘
	multiply(resultf, imgCanny3c, resultf);
	imshow("Resultf", resultf);
	waitKey(0);

	// 转化为8位图像
	resultf.convertTo(result, CV_8UC3);

	// 显示图像
	imshow("Result", result);
}