#include <iostream>
using namespace std;

#include <opencv2\opencv.hpp>
using namespace cv;

int main()
{
	VideoCapture camera;
	cout << "���½�VideoCapture��camera\n";
	Mat frame_color, frame_gray;
	// namedWindow("Camera");
	// cout << "���½�����Camera\n";
	camera.open(0);
	cout << "�ѳ��Դ�����ͷ\n";
	if (!camera.isOpened())
	{
		cout << "Open the camera is faile!\n";
		return -1;
	}
	cout << "Camera open successful!\n";

	//string xmlPath = "D:\\Program Files (x86)\\opencv\\opencv3.1.0\\build\\etc\\haarcascades\\haarcascade_frontalface_default.xml";
	string xmlPath = "D:\\Program Files (x86)\\opencv\\opencv3.1.0\\build\\etc\\haarcascades\\haarcascade_frontalface_alt.xml";
	//string xmlPath = "D:\\Program Files (x86)\\opencv\\opencv3.1.0\\build\\etc\\haarcascades\\haarcascade_eye.xml";
	//string xmlPath = "D:\\Program Files (x86)\\opencv\\opencv3.1.0\\build\\etc\\haarcascades\\haarcascade_lefteye_2splits.xml"; 
	CascadeClassifier ccf;   //��������������
	// Mat img = imread("d:/friends.jpg");
	if (!ccf.load(xmlPath))   //����ѵ���ļ�
	{
		cout << "���ܼ���ָ����xml�ļ�" << endl;
		return 0;
	}
	vector<Rect> faces;  //����һ�������������������

	// ���һ��ͼƬ
	Mat img = imread("C:\\Users\\mengf\\Pictures\\����Ƭ\\37.jpg");
	//resize(img, img, img.size() / 3);
	Mat img_gray;
	cvtColor(img, img_gray, CV_BGR2GRAY);
	ccf.detectMultiScale(img_gray, faces, 1.1, 3, 0, Size(5, 5), Size(100, 100));
	for (vector<Rect>::const_iterator iter = faces.begin(); iter != faces.end(); iter++)
	{
		rectangle(img, *iter, Scalar(0, 0, 255), 2, 8); //������������
		rectangle(img_gray, *iter, Scalar(255, 255, 255));
	}
	//imshow("Picture Color", img);
	//imshow("Picture Gray", img_gray);

	// �������ͷ�������Ƶ
	while (true)
	{
		camera >> frame_color;
		
		cvtColor(frame_color, frame_gray, CV_BGR2GRAY);
		equalizeHist(frame_gray, frame_gray);  //ֱ��ͼ������

		ccf.detectMultiScale(frame_gray, faces, 1.1, 3, 0, Size(10, 10), Size(600, 600)); //�������
		cout << "��⵽" << faces.size() << "������!\n";
		for (vector<Rect>::const_iterator iter = faces.begin(); iter != faces.end(); iter++)
		{
			rectangle(frame_color, *iter, Scalar(0, 0, 255), 2, 8); //������������
			rectangle(frame_gray, *iter, Scalar(255, 255, 255));
		}
		imshow("Color", frame_color);
		imshow("Gray", frame_gray);
		if (waitKey(30) >= 0) break;
	}
	cout << "׼���ͷ�����ͷ\n";
	camera.release();
	cout << "���ͷ�����ͷ\n";
	return 0;
}