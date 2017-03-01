// 3.6.cpp -- 
#include <opencv2\opencv.hpp>
using namespace cv;

#include <gl\glut.h>
#include <gl\GL.h>
using namespace gl;

#include <iostream>
using namespace std;

Mat frame;

int loadTexture()
{
	if (frame.data == NULL)
		return -1;
}

int main()
{
	VideoCapture camera;
	camera.open(0);		// ����������ͷ
	if (!camera.isOpened())
		return -1;

	// ����һ��֧��OpenGL�Ĵ���
	namedWindow("OpenGL Camera", WINDOW_OPENGL);
	destroyWindow("OpenGL Camera");
}