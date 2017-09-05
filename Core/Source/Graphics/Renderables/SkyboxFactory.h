/*
===========================================================================
SkyboxFactory.h

Declares SkyboxFactory class that is responsible for creating Skybox instances.
===========================================================================
*/

#pragma once

namespace s3dge
{
	class Skybox;
	class Cubemap;

	class SkyboxFactory
	{
	public:
		static Skybox*const CreateSkybox(Cubemap*const texture);
	};
}