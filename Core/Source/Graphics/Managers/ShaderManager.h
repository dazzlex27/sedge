/*
===========================================================================
ShaderManager.h

Defines a class responsible for managing ShaderProgram objects.

TODO: standartize all of the manager classes
===========================================================================
*/

#pragma once

#include <map>

namespace s3dge
{
	class ShaderProgram;

	class ShaderManager
	{
	private:
		static std::map<std::string, ShaderProgram*> _programs;
		static bool _initialized;

	public:
		static void Initialize();
		static void Add(const char*const name, const char*const vertexPath, const char*const fragmentPath, const bool overrideExisting = false);
		static ShaderProgram* Get(const char* name);
		static void Dispose();

	private:
		ShaderManager();
		ShaderManager(const ShaderManager& tRef) = delete;
		ShaderManager& operator = (const ShaderManager& tRef) = delete;
		~ShaderManager(void) {}
	};
}