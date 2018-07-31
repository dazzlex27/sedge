/*
===========================================================================
ShaderFactory.cpp

Implements ShaderFactory class
===========================================================================
*/

#include "ShaderFactory.h"
#include "ShaderProgram.h"
#include "System/Logger.h"
#include "System/FileUtils.h"
#include "System/MemoryManagement.h"

using namespace s3dge;

ShaderProgram* ShaderFactory::CreateShaderProgram(const char*const name, const char*const vertexPath, const char*const fragmentPath)
{
	if (strcmp(name, "") == 0)
	{
		LOG_ERROR("Cannot create a shader program with an empty name string");
		return nullptr;
	}

	if (!FileUtils::CheckFileExists(vertexPath))
	{
		LOG_ERROR("Vertex shader path \"", vertexPath, "\"was not found");
		return nullptr;
	}

	if (!FileUtils::CheckFileExists(fragmentPath))
	{
		LOG_ERROR("Fragment shader path \"", fragmentPath, "\"was not found");
		return nullptr;
	}

	ShaderProgram* program = new ShaderProgram(name, vertexPath, fragmentPath);

	if (!program->Load())
	{
		LOG_ERROR("Failed to load shader program: ", name);
		SafeDelete(program);
		return nullptr;
	}

	return program;
}