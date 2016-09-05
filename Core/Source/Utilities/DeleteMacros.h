#pragma once

namespace S3DGE
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