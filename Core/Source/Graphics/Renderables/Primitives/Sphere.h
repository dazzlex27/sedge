#pragma once

#include "Graphics/Renderables/Renderable3D.h"

namespace s3dge
{
	class Shpere : public Renderable3D
	{
	public:
		Shpere();
		Shpere(const uint color);
		~Shpere();

	private:
		void GenerateSphere(const uint color);
	};
}