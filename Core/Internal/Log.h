#pragma once

#include <iostream>

namespace s3dge
{
#define LOG_WARNING(...) Logger::LogEvent(EVENT_TYPE::LOG_WARNING, __VA_ARGS__)
#define LOG_INFO(...) Logger::LogEvent(EVENT_TYPE::LOG_INFO, __VA_ARGS__)
#define LOG_ERROR(...) Logger::LogEvent(EVENT_TYPE::LOG_ERROR, __VA_ARGS__)
#define LOG_FATAL(...) Logger::LogEvent(EVENT_TYPE::LOG_FATAL, __VA_ARGS__)

	enum EVENT_TYPE
	{
		LOG_WARNING,
		LOG_INFO,
		LOG_ERROR,
		LOG_FATAL
	};

	class Logger
	{
		static void Print(int i) { printf("%d", i); }
		static void Print(uint i) { printf("%u", i); }
		static void Print(float f) { printf("%.3f", f); }
		static void Print(double d) { printf("%.6f", d); }
		static void Print(cstring s) { printf("%s", s); }

	public:
		template<typename... Arguments> 
		static void LogEvent(EVENT_TYPE type, Arguments... args)
		{
			switch (type)
			{
			case LOG_WARNING:
				printf("WARNING: ");
				break;
			case LOG_INFO:
				printf("INFO: ");
				break;
			case LOG_ERROR:
				printf("ERROR: ");
				break;
			case LOG_FATAL:
				printf("FATAL ERROR: ");
				break;
			}

			std::initializer_list<int> { ((Print(std::forward<Arguments>(args))), 0)... };
			printf("\n");
		}

		private:
			Logger(void);
			Logger(const Logger& tRef) = delete;				// Disable copy constructor.
			Logger& operator = (const Logger& tRef) = delete;	// Disable assignment operator.
			~Logger(void) = delete;
	};
}