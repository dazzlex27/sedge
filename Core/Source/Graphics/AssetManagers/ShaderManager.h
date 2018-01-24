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
		std::map<std::string, ShaderProgram*> _programs;

	public:
		~ShaderManager();
		void Add(const char*const name, const char*const vertexPath, const char*const fragmentPath, const bool overrideExisting = false);
		ShaderProgram*const GetShader(const char* name);

	private:
		ShaderManager() {}
		ShaderManager(const ShaderManager& tRef) = delete;
		ShaderManager& operator = (const ShaderManager& tRef) = delete;

		friend class GraphicsAssetManagerFactory;
	};
}