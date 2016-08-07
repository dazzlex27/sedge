#pragma once

#include <fstream>
#include "Log.h"

namespace S3DGE
{
	std::string ReadFile(const std::string &filepath)
	{
		std::ifstream ifs((filepath).c_str());
		std::string content(std::istreambuf_iterator<char>(ifs.rdbuf()), std::istreambuf_iterator<char>());

		return content;
	}
}