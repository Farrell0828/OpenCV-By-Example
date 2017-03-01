// 2.10.cpp -- 文件存储写入
#include <opencv2\opencv.hpp>
using namespace cv;

int main(int, char **argv)
{
	// 创建写
	FileStorage fs("test.yml", FileStorage::WRITE);
	// 保存为int
	int fps = 5;
	fs << "fps" << fps;
	// 创建mat文例
	Mat m1 = Mat::eye(2, 3, CV_32F);
	Mat m2 = Mat::ones(3, 2, CV_32F);
	Mat result = (m1 + 1).mul(m1 + 3);
	// 打印结果
	fs << "Result" << result;
	// 释放文件
	fs.release();

	FileStorage fs2("test.yml", FileStorage::READ);

	Mat r;
	fs2["Result"] >> r;
	std::cout << r << std::endl;

	fs2.release();

	return 0;
}