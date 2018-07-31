#include "Logger.h"
#include "DateTime.h"

using namespace s3dge;

std::string Logger::GetLocalTimeString()
{
	auto currentTIme = DateTime::GetCurrentTime();
	
	return currentTIme.ToLongDateTimeString();
}

const char* Logger::GetMessageTypeString(LogEventType eventType)
{
	switch (eventType)
	{
	case EVENT_WARNING:
		return "Warning: ";
		break;
	case EVENT_INFO:
		return "Info: ";
		break;
	case EVENT_ERROR:
		return "Error: ";
		break;
	case EVENT_FATAL:
		return "Fatal: ";
		break;
	case EVENT_OPENGL_ERROR:
		return "OpenGL issue: ";
		break;
	}

	return "<UNSUPPORTED MESSAGE TYPE>";
}