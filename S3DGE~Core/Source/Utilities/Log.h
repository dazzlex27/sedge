#pragma once

#include <iostream>

namespace S3DGE
{
#define LOG_WARNING(x) Logger::LogEvent(EVENT_TYPE::LOG_WARNING, x)
#define LOG_INFO(x) Logger::LogEvent(EVENT_TYPE::LOG_INFO, x)
#define LOG_ERROR(x) Logger::LogEvent(EVENT_TYPE::LOG_ERROR, x)
#define LOG_FATAL(x) Logger::LogEvent(EVENT_TYPE::LOG_FATAL, x)

	enum EVENT_TYPE
	{
		LOG_WARNING,
		LOG_INFO,
		LOG_ERROR,
		LOG_FATAL
	};

	class Logger
	{
	public:
		static void LogEvent(EVENT_TYPE type, const char* message)
		{
			switch (type)
			{
			case LOG_WARNING:
				printf("WARNING: %s\n", message);
				break;
			case LOG_INFO:
				printf("INFO: %s\n", message);
				break;
			case LOG_ERROR:
				printf("ERROR: %s\n", message);
				break;
			case LOG_FATAL:
				printf("FATAL ERROR: %s\n", message);
				break;
			}
		}

		private:
			Logger(void);
			Logger(const Logger& tRef); // disable copy constructor
			Logger& operator = (const Logger& tRef) {}
			~Logger(void) {}
	};
}