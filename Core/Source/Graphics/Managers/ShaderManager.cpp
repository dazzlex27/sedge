/*
===========================================================================
ShaderManager.cpp

Implements ShaderManager class 
===========================================================================
*/

#include "ShaderManager.h"
#include "Graphics/Shaders/ShaderFactory.h"
#include "System/Log.h"
#include "System/DeleteMacros.h"

using namespace s3dge;
using namespace std;

map<string, ShaderProgram*> ShaderManager::_programs;
bool ShaderManager::_initialized;

void ShaderManager::Initialize()
{
	_initialized = true;
}

void ShaderManager::Add(const char*const name, const char*const vertexPath, const char*const fragmentPath, const bool overrideExisting)
{
	if (_initialized)
	{
		if (Get(name) != nullptr)
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

			return;
		}

		ShaderProgram* program = ShaderFactory::CreateShaderProgram(name, vertexPath, fragmentPath);
		if (program != nullptr)
			_programs[name] = program;
	}
	else
	{
		LOG_WARNING("Font manager was not initialized before adding a shader program (", name, ")");
	}
}

ShaderProgram* ShaderManager::Get(const char*const name)
{
	if (_initialized)
	{
		if (_programs.find(name) != _programs.end())
			return _programs[name];

		return nullptr;
	}
	else
	{
		LOG_WARNING("Texture manager was not initialized before getting a shader program (", name, ")");
	}

	return nullptr;
}

void ShaderManager::Dispose()
{
	if (_initialized)
	{
		for (auto item : _programs)
			SafeDelete(item.second);

		_initialized = true;
	}
	else
	{
		LOG_WARNING("Cannot dispose the shader program manager as it was not initialized!");
	}
}
