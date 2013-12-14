// clickStoreRGB.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "RGBRecord.h"

using namespace::std;
using namespace::cv;

Mat img; // 图片
string imgName; // 当前图片路径
vector<RGBRecord> rgbVec;


static void onMouse( int event, int x, int y, int, void* )
{
    if( event != CV_EVENT_LBUTTONDOWN )
        return;
	
	Mat_<Vec3b> _img = img;
	RGBRecord record( _img(y,x)[2], _img(y,x)[1], _img(y,x)[0], y, x, imgName); 
	rgbVec.push_back(record);
	cout << record << endl;
	img = _img;
	
}

void writeVec()
{
	if (rgbVec.empty())
	{
		return;
	}

	// write to txt
	ofstream outfile("rgbStat.txt", ofstream::out | ofstream::app);
	if(!outfile)
	{
		cerr << "unable to open outfile" << endl;
		return ;
	}
	else
	{
		if(outfile)
		{
			// write every record
			for (vector<RGBRecord>::iterator iter = rgbVec.begin() ;
					iter != rgbVec.end() ; ++iter)
			{
				outfile << *iter << endl;
			}
		}
		// close the file
		outfile.close();
		outfile.clear();
	}
}


int _tmain(int argc, _TCHAR* argv[])
{

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
			writeVec();
			break;
		}
	}

	return 0;
}

