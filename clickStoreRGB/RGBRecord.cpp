#include "stdafx.h"

#include <iostream>
#include <fstream>
#include <string>
#include "RGBRecord.h"

ostream& operator << (ostream &out, RGBRecord &record )
{
	out << "r,g,b at (" << (int)record.x << ", "<< (int)record.y << ")"<< endl;
	out << " \tr = " << (int)record.r ;
	out << " \tg = " << (int)record.g ;
	out << " \tb = " << (int)record.b ;
	return out;
}


// write a record to a file
ofstream& operator << (ofstream &file, RGBRecord &record )
{
	// ¸ñÊ½ 255 0 0 test0001.bmp 100 200
	string sp = " ";
	file << (int)(record.r) << sp;
	file << (int)(record.g) << sp;
	file << (int)(record.b) << sp;
	file << record.filename << sp;
	file << (int)(record.x) << sp;
	file << (int)(record.y) << ends;

	return file;
}

