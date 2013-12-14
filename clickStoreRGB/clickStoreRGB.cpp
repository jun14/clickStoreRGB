// clickStoreRGB.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

#include "RGBRecord.h"

using namespace::std;
using namespace::cv;

Mat img; // 图片
string filename; // 当前图片路径
vector<RGBRecord> rgbVec;


static void onMouse( int event, int x, int y, int, void* )
{
    if( event != CV_EVENT_LBUTTONDOWN )
        return;
	
	Mat_<Vec3b> _img = img;
	RGBRecord record( _img(y,x)[2], _img(y,x)[1], _img(y,x)[0], y, x, filename); 
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

string ext(string strFile)
{
	string::size_type found = strFile.rfind(".");
	if( found != string ::npos)
	{
		++found;
		string strExt =  strFile.substr(found);
		// 全部转换成小写
		transform(strExt.begin(), strExt.end(), strExt.begin(), ::tolower);
		return strExt;
	}
	return string();
}

bool isImage(string filename)
{	
	string strExt = ext(filename);
	if(strExt == "jpg" || strExt == "bmp" || strExt == "jpeg" || 
		strExt == "png" )
	{
		cout << "ext is: " << strExt << endl;
		return true;
	}
	return false;
}

bool isVideo(string filename)
{
	string strExt = ext(filename);
	if( strExt == "avi" || strExt == "3gp" || strExt == "rmvb" || 
		strExt == "mp4" || strExt == "wmv" || strExt == "mkv" )
	{
		cout << "ext is: " << strExt << endl;
		return true;
	}
	return false;
}


int _tmain(int argc, _TCHAR* argv[])
{

	cout << "input an file: " <<ends;
	cin >> filename;
	cout << "input accepted : " << filename << endl;

	if(isImage(filename))
	{
		cout << "This is an image." << endl;
	}
	else if(isVideo(filename))
	{
		cout << "This is a vdio." << endl;
	}
	else
	{
		cout << "Unknown-type file." << endl;
	}

	img = imread(filename);
	if(! img.data )                              // Check for invalid input
	{
		cout <<  "Could not open or no such file." << std::endl ;
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

