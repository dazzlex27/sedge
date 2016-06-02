/*
===========================================================================
MemoryManager.h

A custom memory allocator. Basically isn't implemented yet, stay tuned for that.
===========================================================================
*/

#pragma once

#include <vector>
#include <assert.h>
#include "CustomTypes.h"
#include "DeleteMacros.h"

namespace s3dge
{
	class MemoryManager
	{
	private:
		static bool _initialized;
		static void* _head;
		static size_t _size;
		static uint _allocations;

	public:
		static bool Initialize(size_t size);	
		static void Allocate(size_t size);
		static void Deallocate(void* address);
		static bool Dispose();

		size_t GetPoolSize() const { return _size; }
		bool IsInitialized() const { return _initialized; }

	private:
		MemoryManager(void) = delete;
		MemoryManager(const MemoryManager& tRef) = delete;
		MemoryManager& operator =(const MemoryManager& tRef) = delete;
		~MemoryManager() = delete;
	};
}