#include "Logger.h"
#include <iostream>

std::vector<LogEntry> Logger::LogEntries;

void Logger::LogMessage(LogLevel Level, const std::string& Message)
{
	LogEntry Entry;
	Entry.Level = Level;
	Entry.Message = Message;
	LogEntries.push_back(Entry);
	PrintLog(Entry);
}

void Logger::PrintLog(const LogEntry& Entry)
{
	std::string Color;

	switch (Entry.Level)
	{
		case LogLevel::INFO:
			Color = "\x1B[32m";
			break;

		case LogLevel::WARNING:
			Color = "\x1B[33m";
			break;

		case LogLevel::ERROR:
			Color = "\x1B[91m";
			break;
		
		default:
			break;
	}

	std::cout << Color << Entry.Message << "\033[0m" << '\n';
}
