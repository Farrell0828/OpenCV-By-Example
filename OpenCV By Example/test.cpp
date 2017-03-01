#include <iostream>
using namespace std;

#include <opencv2\opencv.hpp>
using namespace cv;

int main()
{
	VideoCapture camera;
	cout << "已新建VideoCapture类camera\n";
	Mat frame_color, frame_gray;
	// namedWindow("Camera");
	// cout << "已新建窗口Camera\n";
	camera.open(0);
	cout << "已尝试打开摄像头\n";
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
	CascadeClassifier ccf;   //创建分类器对象
	// Mat img = imread("d:/friends.jpg");
	if (!ccf.load(xmlPath))   //加载训练文件
	{
		cout << "不能加载指定的xml文件" << endl;
		return 0;
	}
	vector<Rect> faces;  //创建一个容器保存检测出来的脸

	// 检测一张图片
	Mat img = imread("C:\\Users\\mengf\\Pictures\\老照片\\37.jpg");
	//resize(img, img, img.size() / 3);
	Mat img_gray;
	cvtColor(img, img_gray, CV_BGR2GRAY);
	ccf.detectMultiScale(img_gray, faces, 1.1, 3, 0, Size(5, 5), Size(100, 100));
	for (vector<Rect>::const_iterator iter = faces.begin(); iter != faces.end(); iter++)
	{
		rectangle(img, *iter, Scalar(0, 0, 255), 2, 8); //画出脸部矩形
		rectangle(img_gray, *iter, Scalar(255, 255, 255));
	}
	//imshow("Picture Color", img);
	//imshow("Picture Gray", img_gray);

	// 检测摄像头捕获的视频
	while (true)
	{
		camera >> frame_color;
		
		cvtColor(frame_color, frame_gray, CV_BGR2GRAY);
		equalizeHist(frame_gray, frame_gray);  //直方图均衡行

		ccf.detectMultiScale(frame_gray, faces, 1.1, 3, 0, Size(10, 10), Size(600, 600)); //检测人脸
		cout << "检测到" << faces.size() << "个人脸!\n";
		for (vector<Rect>::const_iterator iter = faces.begin(); iter != faces.end(); iter++)
		{
			rectangle(frame_color, *iter, Scalar(0, 0, 255), 2, 8); //画出脸部矩形
			rectangle(frame_gray, *iter, Scalar(255, 255, 255));
		}
		imshow("Color", frame_color);
		imshow("Gray", frame_gray);
		if (waitKey(30) >= 0) break;
	}
	cout << "准备释放摄像头\n";
	camera.release();
	cout << "已释放摄像头\n";
	return 0;
}