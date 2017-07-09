#pragma once

namespace s3dge
{
	class Mesh;
	class Renderable;

	class Renderer
	{
	public:
		virtual void Begin() = 0;
		virtual void Submit(const Renderable* renderable) = 0;
		virtual void Flush() = 0;
		virtual void End() = 0;
	};
}