#include "Mesh2D.h"

using namespace s3dge;
using namespace graphics;
using namespace std;

Mesh2D::Mesh2D(const std::vector<VertexData>& vertices, const std::vector<float> indices, const Color& color)
	: _vertices(vertices), _indices(indices), _color(color)
{
}