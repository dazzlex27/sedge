#pragma once

#include <vector>
#include <GL/glew.h>
#include "S3DGETypes.h"
#include "Buffer.h"
#include "Utilities/DeleteMacros.h"

namespace s3dge
{
	namespace Graphics
	{
		class VertexArray
		{
		private:
			uint m_VertexArrayID;
			std::vector<Buffer*> m_Bufers;

		public:
			VertexArray();
			~VertexArray();

			void AddBuffer(Buffer* buffer, uint index);
			void Bind() const;
			void Unbind() const;
		};
	}
}