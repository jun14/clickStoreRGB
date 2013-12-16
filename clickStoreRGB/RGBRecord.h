// RGBRecord.h 
// 定义存储在txt中的格式
#ifndef RGBRECORD_H 
#define RGBRECORD_H 


#include <iostream>
#include <fstream>
#include <string>

using namespace::std;

class RGBRecord
{
public:
	// constructors
	RGBRecord() : r(0), g(0), b(0), 
				  x(0), y(0), 
				  frameNo(-1), filename() //default
	{}
	RGBRecord(unsigned char r, unsigned char g, unsigned char b): 
			  x(0), y(0), frameNo(-1), filename() // only assign rgb
	{
		this->r = r;
		this->g = g;
		this->b = b;
	}
	RGBRecord(unsigned char r, unsigned char g, unsigned char b, 
			  int x, int y, int frameNo, string filename) // all set
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->x = x;
		this->y = y;
		this->frameNo = frameNo;
		this->filename = filename;
	}

	// interfaces
	// print a record
	friend ostream& operator << (ostream &out,const RGBRecord &record );
	// write a record to a file
	friend ofstream& operator << (ofstream &file,const RGBRecord &record );

private:
	// 定义的顺序很重要
	unsigned char r,g,b;
	int x, y;
	int frameNo;
	string filename;
};



#endif