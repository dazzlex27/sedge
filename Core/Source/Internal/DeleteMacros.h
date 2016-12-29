/*
===========================================================================
DeleteMacros.h

Contains a set of functions for safe deletion of objects
===========================================================================
*/

#pragma once

namespace s3dge
{
	template<typename T>
	inline void SafeDelete(T*& a)
	{
		delete a;
		a = 0;
	}

	template<typename T>
	inline void SafeDeleteArray(T*& a)
	{
		delete[] a;
		a = 0;
	}
}