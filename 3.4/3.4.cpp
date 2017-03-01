// 3.4.cpp -- �ڽ�������ӻ�����������¼�
#include <opencv2\opencv.hpp>
// #include <opencv2\core.hpp>
// #include <opencv2\highgui.hpp>
using namespace cv;

// ����һ�����������滬����λ��ֵ
int blurAmount = 15;

// �������Ļص�����
static void onChange(int pos, void *userInput);

// ���Ļص�
static void onMouse(int event, int x, int y, int, void *userInput);

int main()
{
	// ��ȡͼ��
	Mat lena = imread("C:\\Users\\mengf\\Pictures\\Work Pictures\\lena.jpg");
	Mat photo = imread("C:\\Users\\mengf\\Pictures\\Work Pictures\\photo.jpg");
	// ��������
	namedWindow("Lena");

	// ����һ��������
	createTrackbar("Lena-Track", "Lena", &blurAmount, 30, onChange, &lena);

	setMouseCallback("Lena", onMouse, &lena);

	// ����onChange����ʼ��
	onChange(blurAmount, &lena);

	// �ȴ����̰����˳�
	waitKey(0);

	// ���ٴ���
	destroyWindow("Lena");

	return 0;
}

// �������ص�����
static void onChange(int pos, void *userInput)
{
	if (pos <= 0)
		return;
	Mat imgBlur;		// ����ĸ�������
	Mat *img = (Mat*)userInput;		// ��ȡ����ͼ���ָ��
	blur(*img, imgBlur, Size(pos, pos));	// Ӧ��ģ���˲�
	imshow("Lena", imgBlur);		// չʾ���
}

// ���ص�
static void onMouse(int event, int x, int y, int, void *userInput)
{
	if (event != EVENT_LBUTTONDOWN)
		return;
	Mat *img = (Mat*)userInput;		// ȡ������ͼ���ָ��
	circle(*img, Point(x, y), 10, Scalar(0, 255, 0), 3);	// ����Բ��
	onChange(blurAmount, img);
}