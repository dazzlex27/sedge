#pragma once

namespace s3dge
{
	class Model;

	class ModelFactory
	{
	public:
		Model*const CreateModel(const char*const path);


	};
}