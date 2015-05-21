
#include <boost/lexical_cast.hpp>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>

using namespace std;
using namespace boost::filesystem;
using namespace boost::algorithm;

class FileBox
{
public:
	//FileBox();
	//~FileBox();
	string Fn;
	long Fs;
	FileBox(string a, long b)
	{
		Fn = a; Fs = b;
	}

};

string ShowName(FileBox& rr);

long ShowSize(FileBox& rr);

bool cmp(FileBox a, FileBox b);

vector<FileBox> V(string s_);

