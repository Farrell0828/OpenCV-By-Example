#include <opencv2\opencv.hpp>
using namespace cv;

#include <vector>
using namespace std;

void Cartoon(Mat img);

int main()
{

	// ����ͼƬ�ļ�
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
	// Ӧ����ֵ�˲�ȥ�����ܵ�����
	Mat imgMedian;
	medianBlur(img, imgMedian, 7);
	imshow("Median", imgMedian);
	waitKey(0);

	// ��Canny����Ե
	Mat imgCanny;
	Canny(imgMedian, imgCanny, 50, 150);
	imshow("Canny", imgCanny);
	waitKey(0);

	// ��Ե����
	Mat kernel = getStructuringElement(MORPH_RECT, Size(2, 2));
	dilate(imgCanny, imgCanny, kernel);
	imshow("Canny", imgCanny);
	waitKey(0);

	// ��Եֵ���ŵ�1������ֵ��ת
	imgCanny = imgCanny / 255;
	imgCanny = 1 - imgCanny;
	imshow("Canny", imgCanny);
	waitKey(0);

	// ʹ�ø���ֵ�Ա�������0��1֮�����
	Mat imgCannyf;
	imgCanny.convertTo(imgCannyf, CV_32FC3);
	imshow("Cannyf", imgCannyf);
	waitKey(0);

	// ģ����Ե��ʵ��ƽ��Ч��
	blur(imgCannyf, imgCannyf, Size(5, 5));
	imshow("Cannyf", imgCannyf);
	waitKey(0);

	// Ӧ��˫���˲�����ʵ��ɫ�ʾ��Ȼ�
	Mat imgBF;
	bilateralFilter(img, imgBF, 9, 150.0, 150.0);
	imshow("BF", imgBF);
	waitKey(0);

	// �ض���ɫ
	Mat result = imgBF / 25;
	result = result * 25;
	imshow("Result", result);
	waitKey(0);

	// Ϊ��Ե����3��ͨ��
	Mat imgCanny3c;
	Mat cannyChannels[] = { imgCannyf, imgCannyf, imgCannyf };
	merge(cannyChannels, 3, imgCanny3c);

	// �����ת��Ϊ������
	Mat resultf;
	result.convertTo(resultf, CV_32FC3);
	imshow("Resultf", resultf);
	waitKey(0);

	// ��ɫ�ͱ�Ե�������
	multiply(resultf, imgCanny3c, resultf);
	imshow("Resultf", resultf);
	waitKey(0);

	// ת��Ϊ8λͼ��
	resultf.convertTo(result, CV_8UC3);

	// ��ʾͼ��
	imshow("Result", result);
}