#pragma once
#include"Counter.h"
#include<iostream>
#include<fstream>
#include<string>
#include<ctime>

using std::string;
using std::ios;
using std::ofstream;
using std::endl;
using std::cout;

class Logger {
	string file;
	Counter unorderdTable, avlTable, hashTable;

	void Log() {
		ofstream fileStream;
		fileStream.open(file, ios::out);
		fileStream << "Operations count:" << endl;
		fileStream << "\tUnorderedTable: " << unorderdTable << endl;
		fileStream << "\tAVLTable: " << avlTable << endl;
		fileStream << "\tHashTable: " << hashTable << endl;
	}


};