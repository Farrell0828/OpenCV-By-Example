// 4.4.cpp
#include <opencv2\opencv.hpp>
using namespace cv;

#include <vector>
using namespace std;

void equalize(Mat img);

int main()
{
	// ����ͼƬ�ļ�
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
	// BGRͼ��ת��ΪYCbCr
	Mat ycrcb;
	cvtColor(img, ycrcb, COLOR_BGR2YCrCb);

	// ͼ��ͨ������
	vector<Mat> channels;
	split(ycrcb, channels);

	// ֻ����Yͨ��
	equalizeHist(channels[0], channels[0]);

	// �ϲ����ͨ��
	merge(channels, ycrcb);

	// ��YCrCbת����BGR��ʽ
	cvtColor(ycrcb, result, COLOR_YCrCb2BGR);

	// ��ʾͼ��
	imshow("Equalized", result);
}