/*
===========================================================================
Mesh.h

Declares the Mesh class
===========================================================================
*/

#pragma once

#include <string>
#include <vector>
#include "Renderable3D.h"

namespace s3dge
{
	struct VertexData;
	class VertexBuffer;
	class ElementBuffer;
	class Texture2D;

	class Mesh : public Renderable3D
	{
	protected:
		std::string Name;
		VertexBuffer* VBO;
		ElementBuffer* EBO;
		std::vector<Texture2D*> DiffTextures;
		std::vector<Texture2D*> SpecTextures;

	private:
		Mesh(const char*const name,
			std::vector<VertexData> vertices,
			std::vector<uint> elements,
			std::vector<Texture2D*> diffTextures = std::vector<Texture2D*>(),
			std::vector<Texture2D*> specTextures = std::vector<Texture2D*>());

	public:
		~Mesh();

		const char*const GetName() const { return Name.c_str(); }

		virtual void Draw() const override;

		friend class MeshFactory;
	};
}