#include "SkyboxFactory.h"
#include "Graphics/Renderables/Skybox.h"

using namespace s3dge;

Skybox*const SkyboxFactory::CreateSkybox(Cubemap*const texture)
{
	return new Skybox(texture);
}
