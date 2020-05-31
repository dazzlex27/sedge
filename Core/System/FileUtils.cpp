/*
===========================================================================
FileUtils.h

Contains implementations for file utilities functions
===========================================================================
*/

#include "FileUtils.h"
#include "System/Logger.h"

using namespace std;
using namespace sedge;

string FileUtils::ReadFromFile(const char* filepath)
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

bool FileUtils::CheckFileExists(const char* name)
{
	if (FILE *file = fopen(name, "r"))
	{
		fclose(file);
		return true;
	}
	else
		return false;
}