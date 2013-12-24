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
#include <Windows.h>

#include "RGBRecord.h"

using namespace::std;
using namespace::cv;

Mat img;		// 图片
int frameNum = -1;	// 帧数
string filename;	// 当前图片路径
char sc[500];		// 当前图片路径转换
vector<RGBRecord> rgbVec;



static void onMouse( int event, int x, int y, int, void* )
{
	if( event == CV_EVENT_LBUTTONUP )
	{
		Mat_<Vec3b> _img = img;
		RGBRecord record( _img(y,x)[2], _img(y,x)[1], _img(y,x)[0],
						  y, x, frameNum, filename); 
		rgbVec.push_back(record);
		cout << record << endl;
		img = _img;
		
		return;
	}
	else if ( event == CV_EVENT_RBUTTONUP )
	{
		if(!rgbVec.empty()) // do nothing if empty
		{
			RGBRecord record;
			record = rgbVec.back();
			rgbVec.pop_back();
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |
									FOREGROUND_RED);
			cout << "deleted: "<< record << endl;
			// reset the font color
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x7);
		}
	}
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
	if( strExt == "avi" || strExt == "3gp" || strExt == "rmvb" || strExt == "flv" || 
		strExt == "mp4" || strExt == "wmv" || strExt == "mkv" )
	{
		cout << "ext is: " << strExt << endl;
		return true;
	}
	return false;
}

void dealImage()
{
	img = imread(filename);
	if(! img.data )                              // Check for invalid input
	{
		cout <<  "Could not open or no such image file." << std::endl ;
		return ;
	}
	for (;;)
	{
		const string WIN_SRC  = "src_pic";
		namedWindow( WIN_SRC, CV_WINDOW_AUTOSIZE );// Create a window for display.
		setMouseCallback(WIN_SRC, onMouse);
		imshow( WIN_SRC, img );                   // Show our image inside it.

		char c = (char)waitKey();
		if (c==27) // ESC pressed
		{
			writeVec();
			break;
		}
	}
}

void dealVideo()
{
	VideoCapture capt(filename);
	if(!capt.isOpened())
	{
		cout << "Can't open video file : " << filename << endl;
		return;
	}
	for(;;)
	{
		capt >> img;
		++frameNum ;
		if (img.empty())
		{
			cout << "Video is over." << endl;
			writeVec();
			return;
		}
		cout << "frame = " <<  frameNum << endl;
		const char *WIN_CAP = "src_vid";
		namedWindow(WIN_CAP);
		setMouseCallback(WIN_CAP, onMouse);
		imshow (WIN_CAP, img);

		char c = (char)waitKey();
		// ignore other input keys
		while ( (c!=13) && (c != 27) )
		{
			c = (char)waitKey();
		}
		if (c==13) // ENTER to forward 
		{
			continue;
		}
		if (c==27) // ESC to EXIT
		{
			writeVec();
			break;
		}
	}

}

string& replace_all_distinct(string& str, const string& old_value, const string& new_value)     
{     
    for(string::size_type pos = 0; pos != string::npos; 
		pos += new_value.length() )
	{
		pos=str.find(old_value, pos);
        if( pos != string::npos )     
		{
			str.replace(pos, old_value.length(), new_value);
		}
        else
		{
			break;
		}
	}     
	return str;     
} 

int _tmain(int argc, _TCHAR* argv[])
{
	while (filename.empty())
	{
		if ( argc == 2 ) // drag file input
		{
			wcout << "drag file: " << argv[1] << endl;
			// Converts Unicode string to ANSI
			sprintf(sc,"%S", argv[1]);
			filename = string(sc);
		}
		else // enter the filepath
		{
			cout << "input an file: " <<ends;
			getline(cin, filename);
		}
	} // end while


	replace_all_distinct(filename, string("\\"), string("\\\\") );
	cout << "file accepted: " << filename << endl;

	if(isImage(filename)) // if it's an image
	{
		cout << "This is an image." << endl;
		dealImage();
	}
	else if(isVideo(filename))
	{
		cout << "This is a video." << endl;
		dealVideo();
	}
	else
	{
		cout << "Unknown-type file." << endl;
		// show the results
		getchar();
	}

	return 0;
}

