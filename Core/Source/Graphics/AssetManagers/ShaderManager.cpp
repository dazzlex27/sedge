/*
===========================================================================
ShaderManager.cpp

Implements ShaderManager class 
===========================================================================
*/

#include "ShaderManager.h"
#include "Graphics/Shaders/ShaderFactory.h"
#include "Graphics/Shaders/ShaderProgram.h"
#include "System/Log.h"
#include "System/DeleteMacros.h"

using namespace s3dge;
using namespace std;

void ShaderManager::Add(const char*const name, const char*const vertexPath, const char*const fragmentPath, const bool overrideExisting)
{
	if (GetShader(name) != nullptr)
	{
		if (overrideExisting)
		{
			ShaderProgram* program = ShaderFactory::CreateShaderProgram(name, vertexPath, fragmentPath);
			if (program != nullptr)
				_programs[name] = program;
		}
		else
		{
			LOG_WARNING("Shader program \"", name, "\" already exists and will not be overwritten");
		}
	}
	else
	{
		ShaderProgram* program = ShaderFactory::CreateShaderProgram(name, vertexPath, fragmentPath);
		if (program != nullptr)
			_programs[name] = program;
	}
}

ShaderProgram*const ShaderManager::GetShader(const char*const name)
{
	if (_programs.find(name) != _programs.end())
		return _programs[name];

	return nullptr;
}

ShaderManager::~ShaderManager()
{
	for (auto item : _programs)
		SafeDelete(item.second);
}