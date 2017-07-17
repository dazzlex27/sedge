/*
===========================================================================
Mesh.cpp

Implemlents the Mesh class
===========================================================================
*/

#include "Mesh.h"
#include "Graphics/Textures/Texture2D.h"
#include "Graphics/Buffers/VertexArray.h"
#include "Graphics/Buffers/VertexBuffer.h"
#include "Graphics/Buffers/ElementBuffer.h"
#include "Graphics/Renderers/Renderer.h"
#include "Graphics/Structures/VertexLayout.h"
#include "Graphics/Structures/VertexData.h"
#include "System/DeleteMacros.h"

using namespace s3dge;
using namespace std;

Mesh::Mesh(VertexData* vertices, uint vertexCount, uint* elements, uint elementCount, Texture2D* texture)
	: Renderable(vertices, vertexCount, elements, elementCount, texture)
{
}