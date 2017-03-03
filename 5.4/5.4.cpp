// 5.2.cpp -- AOI Application + ͼ��Ԥ������
#include <opencv2\opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// ͼƬ�����ļ���·��
const String file_path = "C:\\Users\\mengf\\Pictures\\Test Image\\";

Mat RemoveLight(Mat img, Mat pattern, int method);
Mat CalculateLightPattern(Mat img);
void ConnectedComponents(Mat img);

int main()
{
	String img_file = file_path + "pattern1.jpg";
	Mat img = imread(img_file, 0);		// ���ش������ͼ��
	if (img.data == NULL)				// �����ȡͼƬ�ļ�ʧ��
	{
		cout << "Error loading image " << img_file << endl;
		return -1;
	}
	imshow("ԭͼ", img);					// չʾԭͼ

	Mat img_spnoise;					// ȥ�������������ͼ��
	medianBlur(img, img_spnoise, 5);	// ��ֵ�˲�
	imshow("��ֵ�˲����ͼ", img_spnoise);	// չʾ��ֵ�˲����ͼ��

	Mat img_gnoise;						// ȥ����˹�������ͼ��
	GaussianBlur(img, img_gnoise, Size(3, 3), 1.0);		// ��˹�˲�
	imshow("��˹�˲����ͼ", img_gnoise);	// չʾ��˹�˲����ͼ��

	waitKey();
	destroyAllWindows();

	imshow("ԭͼ", img);					// չʾԭͼ
	String pattern_img_file = file_path + "pattern2.jpg";
	Mat pattern = imread(pattern_img_file, 0);
	if (pattern.data == NULL)			// �����ȡͼƬ�ļ�ʧ��
	{
		cout << "Error loading image " << pattern_img_file << endl;
		return -1;
	}
	imshow("����ͼ", pattern);			// չʾ����ͼ
	Mat removed0 = RemoveLight(img, pattern, 0);		// �ò�ַ���
	Mat removed1 = RemoveLight(img, pattern, 1);		// �ó���
	imshow("��ֺ�", removed0);
	imshow("������", removed1);

	waitKey();
	destroyAllWindows();

	imshow("ԭͼ", img);					// չʾԭͼ
	Mat pattern_basic = CalculateLightPattern(img);
	imshow("����ͼ", pattern_basic);		// չʾ����ͼ
	Mat removed0_basic = RemoveLight(img, pattern_basic, 0);	// �ò�ַ���
	Mat removed1_basic = RemoveLight(img, pattern_basic, 1);	// �ó���
	imshow("��ֺ�", removed0_basic);
	imshow("������", removed1_basic);

	waitKey();
	destroyAllWindows();

	// Ϊ�ָ�ͼ���ȶ�ֵ��
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
	if (method == 1)		// ��������ǹ�һ����������
	{
		// �����Ҫ��ͼ�����Ϊ32λ������
		Mat img32, pattern32;
		img.convertTo(img32, CV_32F);
		pattern.convertTo(pattern32, CV_32F);

		aux = 1 - (img32 / pattern32);	// ͼ�����ģʽ
		aux = aux * 255;				// �������������ת����8λ��ʽ
		aux.convertTo(aux, CV_8U);		// ת����8λ��ʽ
	}
	else
	{
		aux = pattern - img;			// ģʽ��ȥͼ��
	}
	return aux;
}

Mat CalculateLightPattern(Mat img)
{
	Mat pattern;
	// �û�������Ч�ķ���������ͼ�����
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