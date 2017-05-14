#include "VertexLayout.h"

using namespace s3dge;

void VertexLayout::AddEntry(LayoutAttribute * attribute)
{
	_attributes.push_back(attribute);
}

void VertexLayout::AddEntry(const char * name, int index, int size, int type, int normalized, int stride, const void * offset)
{
	LayoutAttribute* attribute = new LayoutAttribute;

	attribute->name = name;
	attribute->index = index;
	attribute->size = size;
	attribute->type = type;
	attribute->normalized = normalized;
	attribute->stride = stride;
	attribute->offset = offset;

	_attributes.push_back(attribute);
}
