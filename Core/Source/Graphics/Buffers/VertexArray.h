/*
===========================================================================
VertexArray.h

Designed to store vertex positions before feeding them to OpenGL.
===========================================================================
*/

#pragma once

#include <vector>
#include "CustomTypes.h"

namespace s3dge
{
	class VertexLayout;

	class VertexArray
	{
	private:
		uint _vertexArrayID;

	public:
		VertexArray();
		~VertexArray();

		void SetLayout(VertexLayout* layout);

		void Bind() const;
		void Unbind() const;
		void Draw(uint indicesCount);
	};
}