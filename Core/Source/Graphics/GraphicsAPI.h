/*
===========================================================================
GraphicsAPI.h

Declares functions for calling API-dependent graphics code.
===========================================================================
*/

#pragma once

#include "CustomTypes.h"
#include "Buffers/BufferEnums.h"
#include "Textures/TextureEnums.h"

namespace s3dge
{
	class GraphicsAPI
	{
	public:
		// Buffers
		static void GenBuffers(const uint n, uint*const buffers);
		static void DeleteBuffers(const uint n, uint*const buffers);
		static void BindBuffer(const BufferTarget target, const uint id);
		static void SetBufferData(const BufferTarget target, const uint bufferSize, const void* bufferData, const DrawingMode mode);
		static void* MapBufferForWriting(const BufferTarget target);
		static void UnmapBuffer(const BufferTarget target);

		// Textures
		static void GenTextures(const uint n, uint*const textures);
		static void DeleteTextures(const uint n, uint*const textures);
		static void BindTexture(const TextureTarget target, const uint id);
		static void GenerateMipmap(const TextureTarget target);
		static void ActivateTexture(const uint num);
		//static void SetTexParametri(const TextureTarget target, const Texture)

		static void EnableFaceCulling();
		static void DisableFaceCulling();
		static void SetFaceCulling(const bool cullFaces);

		static void EnableDepthTesting();
		static void DisableDepthTesting();
		static void SetDepthTesting(const bool testDepth);
	};
}