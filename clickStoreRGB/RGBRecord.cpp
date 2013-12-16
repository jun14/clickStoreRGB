#include "stdafx.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "RGBRecord.h"

using namespace::std;

ostream& operator << (ostream &out,const RGBRecord &record )
{
	//out << "r,g,b at (" << (int)record.x << ", "<< (int)record.y << ")"<< endl;
	//out << " \tr = " << (int)record.r ;
	//out << " \tg = " << (int)record.g ;
	//out << " \tb = " << (int)record.b ;
	//return out;

	// 格式: 255 0 0 test0001.bmp 100 200
	string sp = "\t";
	out << (int)(record.r) << sp;
	out << (int)(record.g) << sp;
	out << (int)(record.b) << sp;
	out << record.x << sp;
	out << record.y << sp;
	out << record.frameNo << sp;
	out << record.filename ;

	return out;
}


// write a record to a file
ofstream& operator << (ofstream &file,const RGBRecord &record )
{
	// 格式: 255 0 0 test0001.bmp 100 200
	string sp = "\t";
	file << (int)(record.r) << sp;
	file << (int)(record.g) << sp;
	file << (int)(record.b) << sp;
	file << record.x << sp;
	file << record.y << sp;
	file << record.frameNo << sp;
	file << record.filename ;
	
	return file;
}

