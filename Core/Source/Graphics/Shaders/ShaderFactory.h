/*
===========================================================================
ShaderFactory.h

Takes responsibility for creating ShaderProgram objects
===========================================================================
*/

#pragma once

namespace s3dge
{
	class ShaderProgram;

	class ShaderFactory
	{
	public:
		static ShaderProgram* CreateShaderProgram(const char*const name, const char*const vertexPath, const char*const fragmentPath);

	private:
		ShaderFactory();
		ShaderFactory(const ShaderFactory& tRef) = delete;
		ShaderFactory& operator = (const ShaderFactory& tRef) = delete;
		~ShaderFactory(void) {}
	};
}