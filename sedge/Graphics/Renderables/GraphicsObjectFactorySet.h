#pragma once

#include <Graphics/Renderables/MeshFactory.h>
#include <Graphics/Renderables/ModelFactory.h>
#include <Graphics/Renderables/LabelFactory.h>

namespace sedge
{
	struct GraphicsObjectFactorySet
	{
		MeshFactory MeshFactory;
		ModelFactory ModelFactory;
		LabelFactory LabelFactory;
	};
}