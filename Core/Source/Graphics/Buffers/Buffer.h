#pragma once

#include "S3DGETypes.h"
#include <GL/glew.h>

namespace S3DGE
{
	namespace Graphics
	{
		class Buffer
		{
		private:
			uint bufferID;

		public:
			Buffer(int count, float* data);
			~Buffer();

			void Bind();
			void Unbind();
		};
	}
}