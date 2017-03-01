// 3.4.cpp -- 在界面上添加滑动条和鼠标事件
#include <opencv2\opencv.hpp>
// #include <opencv2\core.hpp>
// #include <opencv2\highgui.hpp>
using namespace cv;

// 创建一个变量来保存滑动条位置值
int blurAmount = 15;

// 滑动条的回调函数
static void onChange(int pos, void *userInput);

// 鼠标的回调
static void onMouse(int event, int x, int y, int, void *userInput);

int main()
{
	// 读取图像
	Mat lena = imread("C:\\Users\\mengf\\Pictures\\Work Pictures\\lena.jpg");
	Mat photo = imread("C:\\Users\\mengf\\Pictures\\Work Pictures\\photo.jpg");
	// 创建窗口
	namedWindow("Lena");

	// 创建一个滑动条
	createTrackbar("Lena-Track", "Lena", &blurAmount, 30, onChange, &lena);

	setMouseCallback("Lena", onMouse, &lena);

	// 调用onChange来初始化
	onChange(blurAmount, &lena);

	// 等待键盘按下退出
	waitKey(0);

	// 销毁窗口
	destroyWindow("Lena");

	return 0;
}

// 滑动条回调方法
static void onChange(int pos, void *userInput)
{
	if (pos <= 0)
		return;
	Mat imgBlur;		// 输出的辅助变量
	Mat *img = (Mat*)userInput;		// 获取输入图像的指针
	blur(*img, imgBlur, Size(pos, pos));	// 应用模糊滤波
	imshow("Lena", imgBlur);		// 展示输出
}

// 鼠标回调
static void onMouse(int event, int x, int y, int, void *userInput)
{
	if (event != EVENT_LBUTTONDOWN)
		return;
	Mat *img = (Mat*)userInput;		// 取得输入图像的指针
	circle(*img, Point(x, y), 10, Scalar(0, 255, 0), 3);	// 绘制圆形
	onChange(blurAmount, img);
}