#pragma once

#include "Graphics/Renderables/LabelFactory.h"
#include "Graphics/Renderables/MeshFactory.h"
#include "Graphics/Renderables/ModelFactory.h"

namespace sedge
{
	struct GraphicsObjectFactorySet
	{
		LabelFactory LabelFactory;
		MeshFactory MeshFactory;
		ModelFactory ModelFactory;
	};
}