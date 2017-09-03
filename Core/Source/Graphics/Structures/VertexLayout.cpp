#include "VertexLayout.h"
#include "VertexData.h"

using namespace s3dge;

static const int GetTypeIntFromTypeEnum(const ElementType type)
{
	switch (type)
	{
	case Float:
		return 0x1406;
	case Ubyte:
		return 0x1401;
	}

	return 0;
}

void VertexLayout::AddEntry(LayoutAttribute*const attribute)
{
	_attributes.push_back(attribute);
}

void VertexLayout::AddEntry(const char* name, const int index, const int size, const ElementType type, const bool normalized, const int stride, const void*const offset)
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
	const int structSize = sizeof(VertexData);

	VertexLayout layout;
	layout.AddEntry("position", 0, 3, Float, false, structSize, (const void*)(offsetof(VertexData, Position)));
	layout.AddEntry("color", 1, 4, Ubyte, true, structSize, (const void*)(offsetof(VertexData, Color)));
	layout.AddEntry("normal", 2, 3, Float, false, structSize, (const void*)(offsetof(VertexData, Normal)));
	layout.AddEntry("uv", 3, 2, Float, false, structSize, (const void*)(offsetof(VertexData, UV)));

	return layout;
}

VertexLayout VertexLayout::GetDefaultVertexLayoutSprite()
{
	const int structSize = sizeof(VertexDataS);

	VertexLayout layout;
	layout.AddEntry("position", 0, 3, Float, false, structSize, (const void*)(offsetof(VertexDataS, Position)));
	layout.AddEntry("color", 1, 4, Ubyte, true, structSize, (const void*)(offsetof(VertexDataS, Color)));
	layout.AddEntry("uv", 3, 2, Float, false, structSize, (const void*)(offsetof(VertexDataS, UV)));
	layout.AddEntry("textureID", 4, 1, Float, false, structSize, (const void*)(offsetof(VertexDataS, TextureID)));

	return layout;
}

VertexLayout VertexLayout::GetDefaultVertexLayoutCb()
{
	const int structSize = sizeof(VertexDataCb);

	VertexLayout layout;
	layout.AddEntry("position", 0, 3, Float, false, structSize, (const void*)(offsetof(VertexDataCb, Position)));
	layout.AddEntry("uv", 1, 3, Float, false, structSize, (const void*)(offsetof(VertexDataCb, UV)));
	
	return layout;
}
