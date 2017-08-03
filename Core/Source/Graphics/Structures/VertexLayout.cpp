#include "VertexLayout.h"
#include "VertexData.h"

using namespace s3dge;

static const int GetTypeIntFromTypeEnum(const ElementType type)
{
	switch (type)
	{
	case FLOAT:
		return 0x1406;
	case UBYTE:
		return 0x1401;
	}

	return 0;
}

void VertexLayout::AddEntry(LayoutAttribute*const attribute)
{
	_attributes.push_back(attribute);
}

void VertexLayout::AddEntry(cstring name, const int index, const int size, const ElementType type, const bool normalized, const int stride, const void*const offset)
{
	LayoutAttribute*const attribute = new LayoutAttribute;

	attribute->name = name;
	attribute->index = index;
	attribute->size = size;
	attribute->type = GetTypeIntFromTypeEnum(type);
	attribute->normalized = normalized;
	attribute->stride = stride;
	attribute->offset = offset;

	_attributes.push_back(attribute);
}

VertexLayout VertexLayout::GetDefaultVertexLayout()
{
	VertexLayout layout;
	layout.AddEntry("position", 0, 3, ElementType::FLOAT, false, sizeof(VertexData), (const void*)(offsetof(VertexData, VertexData::Position)));
	layout.AddEntry("color", 1, 4, ElementType::UBYTE, true, sizeof(VertexData), (const void*)(offsetof(VertexData, VertexData::Color)));
	layout.AddEntry("normal", 2, 3, ElementType::FLOAT, false, sizeof(VertexData), (const void*)(offsetof(VertexData, VertexData::Normal)));
	layout.AddEntry("uv", 3, 2, ElementType::FLOAT, false, sizeof(VertexData), (const void*)(offsetof(VertexData, VertexData::UV)));
	layout.AddEntry("textureID", 4, 1, ElementType::FLOAT, false, sizeof(VertexData), (const void*)(offsetof(VertexData, VertexData::TextureID)));

	return layout;
}
