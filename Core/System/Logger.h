/*
===========================================================================
Logger.h

Prints messages with timestamps to the console.

Do not use functions directly, prefer macros instead.
===========================================================================
*/

#pragma once

#include <iostream>
#include <CustomTypes.h>

namespace sedge
{
#define LOG_WARNING(...) Logger::LogEvent(sedge::LogEventType::EVENT_WARNING, __VA_ARGS__)
#define LOG_INFO(...) Logger::LogEvent(sedge::LogEventType::EVENT_INFO, __VA_ARGS__)
#define LOG_ERROR(...) Logger::LogEvent(sedge::LogEventType::EVENT_ERROR, __VA_ARGS__)
#define LOG_FATAL(...) Logger::LogEvent(sedge::LogEventType::EVENT_FATAL, __VA_ARGS__)
#define LOG_OPENGL_ISSUE(...) Logger::LogEvent(sedge::LogEventType::EVENT_OPENGL_ERROR, __VA_ARGS__)

	enum LogEventType
	{
		EVENT_WARNING,
		EVENT_INFO,
		EVENT_ERROR,
		EVENT_FATAL,
		EVENT_OPENGL_ERROR
	};

	class Logger
	{
		static void Print(int i) { std::cout << i; }
		static void Print(uint i) { std::cout << i; }
		static void Print(float f) { printf("%.3f", f); }
		static void Print(double d) { printf("%.6f", d); }
		static void Print(const char* s) { std::cout << s; }
		static void Print(bool b) { std::cout << b ? "true" : "false"; }
		static void Print(const std::string& s) { std::cout << s; }

	public:
		template<typename... Arguments> 
		static void LogEvent(LogEventType type, Arguments... args)
		{
			std::cout << GetLocalTimeString();
			std::cout << " - ";
			std::cout << GetMessageTypeString(type);
			std::initializer_list<int> { ((Print(std::forward<Arguments>(args))), 0)... };
			std::cout << std::endl;
		}

	private:
		static std::string GetLocalTimeString();
		static const char* GetMessageTypeString(LogEventType);

		private:
			Logger(void);
			Logger(const Logger& tRef) = delete;				// Disable copy constructor.
			Logger& operator = (const Logger& tRef) = delete;	// Disable assignment operator.
			~Logger(void) = delete;
	};
}