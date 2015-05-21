#include "Add.h"

string ShowName(FileBox& rr)
{
	return rr.Fn;
}
long ShowSize(FileBox& rr)
{
	return rr.Fs;
}

bool cmp(FileBox a, FileBox b)
{
	return a.Fs < b.Fs;
}

vector<FileBox> V(string s_)
{
	ifstream TSV_file;
	TSV_file.open(s_, ifstream::in);
	string file_text = {};
	while (!TSV_file.eof())
	{
		file_text += TSV_file.get();
	}
	TSV_file.close();

	vector<string> v;
	vector<FileBox> l;
	vector<string>::iterator pd;
	vector<FileBox>::iterator it;

	split(v, file_text, is_any_of("\n"));
	for (pd = v.begin() + 1; pd != v.end() - 1; pd++)         //v.end() -- this is not a kind of FileBox, don't open it!
	{
		vector<string> v_child;
		split(v_child, *pd, is_any_of("\t"), token_compress_on);
		l.push_back(FileBox(v_child[2], boost::lexical_cast<long>(v_child[1])));
	}

	sort(l.begin(), l.end(), cmp);
	return l;
}