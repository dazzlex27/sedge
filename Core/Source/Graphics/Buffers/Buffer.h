/*
===========================================================================
Buffer.h

Defines base class for object buffers.
===========================================================================
*/

#pragma once

#include "CustomTypes.h"

namespace s3dge
{
	enum DrawingMode
	{
		STATIC_DRAW,
		DYNAMIC_DRAW,
		STREAM_DRAW
	};

	class Buffer
	{
	protected:
		id BufferID;
		void* DataPtr;
		uint ElementSize;
		uint ElementCount;

	protected:
		Buffer(const uint elementSize, const uint elementCount, void*const dataPtr = nullptr)
			: ElementSize(elementSize), ElementCount(elementCount), DataPtr(dataPtr) {}

	public:
		virtual ~Buffer() {}

	public:
		inline const id GetBufferID() const { return BufferID; }
		inline const void* GetDataPointer() { return DataPtr; }
		inline const uint GetCount() const { return ElementCount; }
		inline const uint GetElementSize() const { return ElementSize; }
		inline const uint GetTotalLength() const { return ElementCount * ElementSize; }

		virtual void SetDataPointer(void*const dataPtr) { DataPtr = dataPtr; }

		inline virtual void Bind() const = 0;
		inline virtual void Unbind() const = 0;
	};
}