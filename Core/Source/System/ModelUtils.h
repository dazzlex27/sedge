#pragma once

#include <vector>
#include "CustomTypes.h"

namespace s3dge
{
	class Model;
	class Mesh;

	class ModelUtils
	{
	public:
		static Model* ReadFromFile(const char* filepath);

	private:
		ModelUtils(void);
		ModelUtils(const ModelUtils& tRef) = delete;				// Disable copy constructor.
		ModelUtils& operator = (const ModelUtils& tRef) = delete;	// Disable assignment operator.
		~ModelUtils(void) {}
	};
}