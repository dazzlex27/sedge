#pragma once

namespace sedge
{
	class Model;

	class ModelFactory
	{
	public:
		Model*const CreateModel(const char*const path);


	};
}