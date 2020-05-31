#include "ModelFactory.h"
#include "System/ModelUtils.h"

using namespace sedge;

Model*const ModelFactory::CreateModel(const char*const path)
{
	return ModelUtils::ReadFromFile(path);
}
