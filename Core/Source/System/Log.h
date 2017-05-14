/*
===========================================================================
Log.h

A simple logging mechanism. Supports printing 4 types of messages to console.

Do not use functions directly, prefer macros instead.
===========================================================================
*/

#pragma once

#include <iostream>
#include "CustomTypes.h"

namespace s3dge
{
#define LOG_WARNING(...) Logger::LogEvent(s3dge::EVENT_TYPE::EVENT_WARNING, __VA_ARGS__)
#define LOG_INFO(...) Logger::LogEvent(s3dge::EVENT_TYPE::EVENT_INFO, __VA_ARGS__)
#define LOG_ERROR(...) Logger::LogEvent(s3dge::EVENT_TYPE::EVENT_ERROR, __VA_ARGS__)
#define LOG_FATAL(...) Logger::LogEvent(s3dge::EVENT_TYPE::EVENT_FATAL, __VA_ARGS__)
#define LOG_OPENGL_ISSUE(...) Logger::LogEvent(s3dge::EVENT_TYPE::EVENT_OPENGL_ERROR, __VA_ARGS__)

	enum EVENT_TYPE
	{
		EVENT_WARNING,
		EVENT_INFO,
		EVENT_ERROR,
		EVENT_FATAL,
		EVENT_OPENGL_ERROR
	};

	class Logger
	{
		static void Print(int i) { printf("%d", i); }
		static void Print(uint i) { printf("%u", i); }
		static void Print(float f) { printf("%.3f", f); }
		static void Print(double d) { printf("%.6f", d); }
		static void Print(cstring s) { printf("%s", s); }
		static void Print(bool b) { if (b) printf("true"); else printf("false"); }

	public:
		template<typename... Arguments> 
		static void LogEvent(EVENT_TYPE type, Arguments... args)
		{
			switch (type)
			{
			case EVENT_WARNING:
				printf("WARNING: ");
				break;
			case EVENT_INFO:
				printf("INFO: ");
				break;
			case EVENT_ERROR:
				printf("ERROR: ");
				break;
			case EVENT_FATAL:
				printf("FATAL ERROR: ");
				break;
			case EVENT_OPENGL_ERROR:
				printf("OPENGL ISSUE: ");
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