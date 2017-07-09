#pragma once

#include <vector>

namespace s3dge
{
	enum ElementType
	{
		FLOAT,
		UBYTE,
	};

	struct LayoutAttribute
	{
		const char* name;
		int index;
		int size;
		int type;
		int normalized;
		int stride;
		const void* offset;
	};

	class VertexLayout
	{
	private:
		std::vector<LayoutAttribute*> _attributes;

	public:
		inline const std::vector<LayoutAttribute*>& GetAttributes() const { return _attributes; }

		void AddEntry(LayoutAttribute* attribute);
		void AddEntry(const char* name, int index, int size, ElementType type, int normalized, int stride, const void* offset);
	};
}