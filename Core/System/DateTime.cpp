#include "DateTime.h"
#include <ctime>
#include <sstream>
#include <iomanip>

#include "Stopwatch.h"

using namespace sedge;

DateTime DateTime::GetCurrentTime()
{
	return DateTime();
}

std::string DateTime::ToShortDateString() const
{
	auto timeNow = std::chrono::system_clock::to_time_t(_timePoint);
	std::tm localTime = *std::localtime(&timeNow);

	std::string str;
	str.append(std::to_string(localTime.tm_mday));
	str.append("-");
	str.append(std::to_string(localTime.tm_mon));
	str.append("-");
	str.append(std::to_string(localTime.tm_year));

	return str;
}

std::string DateTime::ToShortTimeString() const
{
	auto timeNow = std::chrono::system_clock::to_time_t(_timePoint);
	std::tm localTime = *std::localtime(&timeNow);

	std::string str;
	str.append(std::to_string(localTime.tm_hour));
	str.append(":");
	str.append(std::to_string(localTime.tm_min));
	str.append(":");
	str.append(std::to_string(localTime.tm_sec));

	return str;
}

std::string DateTime::ToLongDateTimeString() const
{
	std::time_t timeNow = std::chrono::system_clock::to_time_t(_timePoint);

	std::tm localTime = *std::localtime(&timeNow);
	std::stringstream ss;
	ss << std::put_time(&localTime, "%c");

	return ss.str().c_str();
}

//TimeSpan sedge::operator-(const DateTime& time1, const DateTime& time2)
//{
//	return TimeSpan();
//}