#include "ModelFactory.h"
#include "System/ModelUtils.h"

using namespace s3dge;

Model*const ModelFactory::CreateModel(const char*const path)
{
	return ModelUtils::ReadFromFile(path);
}
