#pragma once

#include <CustomTypes.h>

namespace sedge
{
	class FrameBuffer
	{
	private:
		ID _bufferID;

	public:
		FrameBuffer();
		~FrameBuffer();

		void Bind() const;
		void Unbind() const;

		const bool IsComplete() const;
		
		void AttachColor(const ID texture);
		void AttachDepth(const ID texture);
		void AttachStencil(const ID texture);
	};
}