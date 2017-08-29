#pragma once

#include "CustomTypes.h"
#include "Buffers/BufferEnums.h"
#include "Textures/TextureEnums.h"

namespace s3dge
{
	class RenderSystem
	{
	public:
		// Buffers
		static void GenBuffers(const uint n, uint*const buffers);
		static void DeleteBuffers(const uint n, uint*const buffers);
		static void BindBuffer(const BufferTarget target, const uint id);

		// Textures
		static void GenTextures(const uint n, uint*const textures);
		static void DeleteTextures(const uint n, uint*const textures);
		static void BindTexture(const TextureTarget target, const uint id);
		static void GenerateMipmap(const TextureTarget target);
		//static void SetTexParametri(const TextureTarget target, const Texture)

		static void EnableFaceCulling();
		static void DisableFaceCulling();
		static void SetFaceCulling(const bool cullFaces);

		static void EnableDepthTesting();
		static void DisableDepthTesting();
		static void SetDepthTesting(const bool testDepth);
	};
}