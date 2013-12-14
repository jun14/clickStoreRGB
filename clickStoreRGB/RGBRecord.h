// RGBRecord.h 
// 定义存储在txt中的格式
#ifndef RGBRECORD_H 
#define RGBRECORD_H 


#include <iostream>
#include <fstream>
#include <string>

using namespace::std;

typedef unsigned char uchar;

class RGBRecord
{
public:
	// constructors
	RGBRecord() : r(0), g(0), b(0), x(0), y(0), filename() //default
	{}
	RGBRecord(uchar r, uchar g, uchar b): x(0), y(0) , filename() // only assign rgb
	{
		this->r = r;
		this->g = g;
		this->b = b;
	}
	RGBRecord(uchar r, uchar g, uchar b, int x, int y, string filename) // all set
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->x = x;
		this->y = y;
		this->filename = filename;
	}

	// interfaces
	// print a record
	friend ostream& operator << (ostream &out, RGBRecord &record );
	// write a record to a file
	friend ofstream& operator << (ofstream &file, RGBRecord &record );

private:
	uchar r;
	uchar g;
	uchar b;
	int x, y;
	string filename;
};



#endif