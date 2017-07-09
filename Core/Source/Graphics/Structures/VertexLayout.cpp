#include "VertexLayout.h"

using namespace s3dge;

int GetTypeIntFromTypeEnum(ElementType type)
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

void VertexLayout::AddEntry(LayoutAttribute* attribute)
{
	_attributes.push_back(attribute);
}

void VertexLayout::AddEntry(const char * name, int index, int size, ElementType type, int normalized, int stride, const void * offset)
{
	LayoutAttribute* attribute = new LayoutAttribute;

	attribute->name = name;
	attribute->index = index;
	attribute->size = size;
	attribute->type = GetTypeIntFromTypeEnum(type);
	attribute->normalized = normalized;
	attribute->stride = stride;
	attribute->offset = offset;

	_attributes.push_back(attribute);
}
