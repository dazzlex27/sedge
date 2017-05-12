#pragma once

namespace s3dge
{
	namespace graphics
	{
		class Renderable
		{
			virtual void Render() const = 0;
		};
	}
}