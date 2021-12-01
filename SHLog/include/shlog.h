#pragma once

#include <iostream>

#include <string>
#include <sstream>

#include <chrono>
#include <iomanip>

#include <windows.h>

/*
	Pattern Keys:
	%t = Current time (eg. 01:20:03)
	%s = Severity (eg. warn, info)
	%c = Severity color
	%m = Message 
*/

namespace shlog {
	std::string GetCurrentTimeAsString() {
		auto t = std::time(nullptr);
		auto tm = *std::localtime(&t);

		std::ostringstream oss;
		oss << std::put_time(&tm, "%H:%M:%S");
		return oss.str();
	}

	enum LogType
	{
		Trace = 0,
		Info = 1,
		Warn = 2,
		Error = 3,
		Critical = 4
	};

	std::string LogTypeToString(LogType type)
	{
		switch (type)
		{
		case shlog::Trace: return "trace";
		case shlog::Info: return "info";
		case shlog::Warn: return "warn";
		case shlog::Error: return "error";
		case shlog::Critical: return "critical";
		}
	}
	int LogTypeToWindowsColorNum(LogType type)
	{
		switch (type)
		{
		case shlog::Trace: return 7;
		case shlog::Info: return 10;
		case shlog::Warn: return 14;
		case shlog::Error: return 12;
		case shlog::Critical: return 4;
		}
	}

	class ConsoleLogger {
	public:
		void Trace(std::string message) 
		{
			Log(message, LogType::Trace);
		}
		void Info(std::string message)
		{
			Log(message, LogType::Info);
		}
		void Warn(std::string message)
		{
			Log(message, LogType::Warn);
		}
		void Error(std::string message)
		{
			Log(message, LogType::Error);
		}
		void Critical(std::string message)
		{
			Log(message, LogType::Critical);
		}

		void Log(std::string message, LogType type) {
			std::string finalMsg = m_Pattern;

			HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

			if (finalMsg.find("%t") != std::string::npos)
				finalMsg.replace(finalMsg.find("%t"), 2, GetCurrentTimeAsString());
			if (finalMsg.find("%s") != std::string::npos)
				finalMsg.replace(finalMsg.find("%s"), 2, LogTypeToString(type));
			if (finalMsg.find("%m") != std::string::npos)
				finalMsg.replace(finalMsg.find("%m"), 2, message);
			if (finalMsg.find("%c") != std::string::npos)
			{
				SetConsoleTextAttribute(h, LogTypeToWindowsColorNum(type));
				finalMsg.replace(finalMsg.find("%c"), 2, "");
			}

			std::cout << finalMsg << "\n";
			SetConsoleTextAttribute(h, 7);
		}

		void SetPattern(std::string pattern) { m_Pattern = pattern; }
	private:
		std::string m_Pattern = "%c[%s] %t: %m";
	};
}