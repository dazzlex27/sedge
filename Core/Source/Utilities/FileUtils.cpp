/*
===========================================================================
FileUtils.h

Contains implementations for file utilities functions
===========================================================================
*/

#include "FileUtils.h"
#include "../Internal/Log.h"

using namespace std;
using namespace s3dge;

string FileUtils::ReadFromFile(cstring filepath)
{
	ifstream ifs(filepath);
	string content(istreambuf_iterator<char>(ifs.rdbuf()), istreambuf_iterator<char>());

	return content;
}

string FileUtils::ReadFromFile(const string& filepath)
{
	ifstream ifs((filepath).c_str());
	string content(istreambuf_iterator<char>(ifs.rdbuf()), istreambuf_iterator<char>());

	return content;
}

bool FileUtils::CheckFileExists(cstring name)
{
	if (FILE *file = fopen(name, "r"))
	{
		fclose(file);
		return true;
	}
	else
		return false;
}