#pragma once

namespace s3dge
{
	namespace graphics
	{
		class Mesh;

		class Renderer
		{
		public:
			virtual void Begin() = 0;
			virtual void SubmitMesh(const Mesh* mesh) = 0;
			virtual void Flush() = 0;
			virtual void End() = 0;
		};
	}
}