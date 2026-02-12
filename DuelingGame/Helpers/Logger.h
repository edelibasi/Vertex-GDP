#pragma once
#include <string>
#include <vector>

enum class LogLevel: uint8_t
{
	INFO,
	WARNING,
	ERROR,
	DEFAULT
};

struct LogEntry
{
	std::string Message;
	LogLevel Level;
};

class Logger
{
public:
	static std::vector<LogEntry> LogEntries;
	static void LogMessage(LogLevel Level, const std::string& Message);
	static void PrintLog(const LogEntry& Entry);
};
