// clickStoreRGB.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
#include <string>
#include <fstream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "RGBRecord.h"

using namespace::std;
using namespace::cv;

Mat img; // 图片
string imgName; // 当前图片路径

static void onMouse( int event, int x, int y, int, void* )
{
    if( event != CV_EVENT_LBUTTONDOWN )
        return;
	
	Mat_<Vec3b> _img = img;
	RGBRecord record( _img(y,x)[2], _img(y,x)[1], _img(y,x)[0], y, x, imgName); 
	cout << record << endl;
	img = _img;
	
}




int _tmain(int argc, _TCHAR* argv[])
{
	//IplImage *img=cvLoadImage("adc.bmp");
	//int x=0;
	//int y=0;
	//cvNamedWindow("demo");
	// cvSetMouseCallback("demo",cvmovecallback,(void*)img);
	//cvShowImage("demo",img);


	cout << "input an image: " <<ends;
	cin >> imgName;
	cout << "input accepted : " << imgName << endl;
	img = imread(imgName);
	if(! img.data )                              // Check for invalid input
	{
		cout <<  "Could not open or find the image" << std::endl ;
		return -1;
	}
	
	for (;;)
	{
		const string WIN_SRC  = "src";
		namedWindow( WIN_SRC, CV_WINDOW_AUTOSIZE );// Create a window for display.
		setMouseCallback(WIN_SRC, onMouse);
		imshow( WIN_SRC, img );                   // Show our image inside it.

		char c = (char)waitKey();
		if (c==27)
		{
			break;
		}
	}

	return 0;
}

