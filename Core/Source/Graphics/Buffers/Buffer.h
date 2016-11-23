#pragma once

#include <GL/glew.h>
#include "CustomTypes.h"

namespace s3dge
{
	namespace Graphics
	{
		class Buffer
		{
		private:
			uint _bufferID;
			uint _componentCount;

		public:
			Buffer(float* data, int count, uint componentCount);
			~Buffer();

			inline const uint GetComponentCount() const { return _componentCount; }

			void Bind();
			void Unbind();
		};
	}
}