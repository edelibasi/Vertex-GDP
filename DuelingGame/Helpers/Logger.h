#pragma once
#include <string>
#include <vector>

enum class LogLevel
{
	INFO,
	WARNING,
	ERROR,
	DEFAULT
};

struct LogEntry
{
	LogLevel Level;
	std::string Message;
};

class Logger
{
public:
	static std::vector<LogEntry> LogEntries;
	static void LogMessage(LogLevel Level, const std::string& Message);
	static void PrintLog(const LogEntry& Entry);
};

