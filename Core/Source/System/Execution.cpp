#include "Execution.h"
#include <exception>
#include <string>

void s3dge::TerminateProgram(const char*const message)
{
	throw std::string(message);
}