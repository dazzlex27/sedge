/*
===========================================================================
GraphicsAPI.h

Declares functions for calling API-dependent graphics code.
===========================================================================
*/

#pragma once

#include <CustomTypes.h>
#include "Buffers/BufferEnums.h"
#include "Textures/TextureEnums.h"
#include "Shaders/ShaderEnums.h"
#include "DrawingEnums.h"

namespace sedge
{
	class GraphicsAPI
	{
	public:
		// Buffers
		static void GenBuffers(const uint n, ID*const buffers);
		static void DeleteBuffers(const uint n, ID*const buffers);
		static void BindBuffer(const BufferTarget target, const ID bufferID);
		static void SetBufferData(const BufferTarget target, const uint bufferSize, const void* bufferData, const DrawingMode mode);
		static void* MapBufferForWriting(const BufferTarget target);
		static void UnmapBuffer(const BufferTarget target);

		// VAO
		/*static void GenVertexArrays(const uint n, ID*const arrays);
		static void DeleteVertexArrays(const uint n, ID*const arrays);
		static void BindVertexArray(const ID id);*/
		static void EnableVertexAttributeArray(const uint index);
		static void VertexAttributePointer(const uint index, const int size, const int type, const int normalized, const int stride, const void*const offset);
		
		// Drawing
		static void DrawArrays(const PrimitiveType primitiveType, const int first, const uint count);
		static void DrawElements(const PrimitiveType primitiveType, const uint count, const ValueType type, const void*const elements);
		static void DrawTrianglesIndexed(const uint elementCount);

		// Textures
		static void GenTextures(const uint n, ID*const textures);
		static void DeleteTextures(const uint n, ID*const textures);
		static void BindTexture(const TextureTarget target, const ID textureID);
		static void LoadTex2DImage(const int level, const ColorCode internalFormat, const int width, const int height, const int border, const ColorCode format, const ValueType valueType, const void*const pixels);
		static void LoadCubemapImage(const uint num, const int level, const ColorCode internalFormat, const int width, const int height, const int border, const ColorCode format, const ValueType valueType, const void*const pixels);
		static void GenerateMipmap(const TextureTarget target);
		static void ActivateTexture(const uint num);
		static void SetTextureWrapMode(const TextureTarget target, const TextureWrap wrap, const TextureWrapMode mode);
		static void SetTextureFilterMode(const TextureTarget target, const TextureFilter filter, const TextureFilterMode mode);

		// Framebuffer
		static void GenFramebuffers(const uint n, ID*const buffers);
		static void DeleteFramebuffers(const uint n, ID*const buffers);
		static void BindFramebuffer(const ID bufferID);
		static const bool IsFramebufferComplete(const ID bufferID);
		static void AttachTextureToFramebuffer(const ID textureID);

		// Shaders
		static const ID CreateShaderProgram();
		static void LinkShaderProgram(const ID programID);
		static void ValidateShaderProgram(const ID programID);
		static const ID CreateShader(const ShaderTarget target);
		static void DeleteShaderProgram(const ID programID);
		static void DeleteShader(const ID shaderID);
		static void AttachShader(const ID programID, const ID shaderID);
		static void DetachShader(const ID programID, const ID shaderID);
		static const bool CompileShader(const ID shaderID);
		static char* GetShaderInfoLog(const ID shaderID);
		static void BindShaderProgram(const ID programID);
		static void LoadShaderSource(const ID shaderID, const char*const source);
		static const int GetUniformLocation(const ID programID, const char*const name);
		static void SetUniformMatrix4(const int location, const int count, const bool transpose, const float*const values);
		static void SetUniform1f(const int location, const float value);
		static void SetUniform2f(const int location, const float value1, const float value2);
		static void SetUniform3f(const int location, const float value1, const float value2, const float value3);
		static void SetUniform4f(const int location, const float value1, const float value2, const float value3, const float value4);
		static void SetUniform1i(const int location, const int value);
		static void SetUniform1iv(const int location, const int count, const int*const values);

		// General
		static const bool Initialize();
		static void Dispose();

		static void Clear();

		static void SetViewPort(const int x, const int y, const int width, const int height);

		static void EnableDepthMask();
		static void DisableDepthMask();
		static void SetDepthMask(const bool useMask);

		static void EnableFaceCulling();
		static void DisableFaceCulling();
		static void SetFaceCulling(const bool cullFaces);

		static void EnableBlending();
		static void DisableBlending();
		static void SetBlending(const bool blend);
		static void SetStandartBlending();

		static void EnableDepthTesting();
		static void DisableDepthTesting();
		static void SetDepthTesting(const bool testDepth);

		static void SetWindingOrder(const WindingOrder order);

		static char* GetVersion();
		static char* GetRenderingDevice();
		static char* GetExtensions();
	};
}