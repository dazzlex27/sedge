/*
===========================================================================
FileUtils.h

Aggregates all the basic components of the engine in a single header file.
This file is included by the main header S3DGE.h
===========================================================================
*/

#pragma once

#include <fstream>
#include <CustomTypes.h>

namespace s3dge
{
	class FileUtils
	{
	public:
		static std::string ReadFromFile(const char* filepath);
		static std::string ReadFromFile(const std::string& filepath);
		static bool CheckFileExists(const char* name);

	private:
		FileUtils(void);
		FileUtils(const FileUtils& tRef) = delete;				// Disable copy constructor.
		FileUtils& operator = (const FileUtils& tRef) = delete;	// Disable assignment operator.
		~FileUtils(void) {}
	};
}