// 2.10.cpp -- �ļ��洢д��
#include <opencv2\opencv.hpp>
using namespace cv;

int main(int, char **argv)
{
	// ����д
	FileStorage fs("test.yml", FileStorage::WRITE);
	// ����Ϊint
	int fps = 5;
	fs << "fps" << fps;
	// ����mat����
	Mat m1 = Mat::eye(2, 3, CV_32F);
	Mat m2 = Mat::ones(3, 2, CV_32F);
	Mat result = (m1 + 1).mul(m1 + 3);
	// ��ӡ���
	fs << "Result" << result;
	// �ͷ��ļ�
	fs.release();

	FileStorage fs2("test.yml", FileStorage::READ);

	Mat r;
	fs2["Result"] >> r;
	std::cout << r << std::endl;

	fs2.release();

	return 0;
}