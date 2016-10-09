#pragma once

#include <fstream>
#include "Log.h"

namespace s3dge
{
	class FileIO
	{
	public:
		static std::string ReadFromFile(cstring filepath)
		{
			std::ifstream ifs(filepath);
			std::string content(std::istreambuf_iterator<char>(ifs.rdbuf()), std::istreambuf_iterator<char>());

			return content;
		}

		static std::string ReadFromFile(const std::string& filepath)
		{
			std::ifstream ifs((filepath).c_str());
			std::string content(std::istreambuf_iterator<char>(ifs.rdbuf()), std::istreambuf_iterator<char>());

			return content;
		}

	private:
		FileIO(void);
		FileIO(const FileIO& tRef) = delete;				// Disable copy constructor.
		FileIO& operator = (const FileIO& tRef) = delete;	// Disable assignment operator.
		~FileIO(void) {}
	};
	
}