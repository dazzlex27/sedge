/*
===========================================================================
DateTime.h

Wrapper class for dealing with time.
Since dealing with time in C++ is a bit hectic, all standart time-related classes should be encapsulated to this class.
===========================================================================
*/

#pragma once

#include <chrono>
#include <string>

namespace s3dge
{
	class DateTime
	{
		typedef std::chrono::system_clock clock;

	private:
		std::chrono::time_point<clock> _timePoint;

	public:
		DateTime()
		{
			_timePoint = clock::now();
		}

		DateTime(const DateTime& time)
		{
			_timePoint = time._timePoint;
		}

		static DateTime GetCurrentTime();

		std::string ToShortDateString() const;
		std::string ToShortTimeString() const;
		std::string ToLongDateTimeString() const;

		//friend TimeSpan operator -(const DateTime& time1, const DateTime& time2);
	};
}