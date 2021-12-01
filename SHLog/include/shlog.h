#pragma once

#include <iostream>

#include <string>
#include <sstream>

#include <chrono>
#include <iomanip>

/*
	Pattern Keys:
	%t = Current time (eg. 01:20:03)
	%s = Severity (eg. warn, info)
	%m = Message 
*/

namespace shlog {
	std::string GetCurrentTime() {
		auto t = std::time(nullptr);
		auto tm = *std::localtime(&t);

		std::ostringstream oss;
		oss << std::put_time(&tm, "%H:%M:%S");
		return oss.str();
	}

	enum LogType
	{
		Trace, Info, Warn, Error, Critical
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

			if (finalMsg.find("%t") != std::string::npos)
				finalMsg.replace(finalMsg.find("%t"), 2, GetCurrentTime());
			if (finalMsg.find("%s") != std::string::npos)
				finalMsg.replace(finalMsg.find("%s"), 2, LogTypeToString(type));
			if (finalMsg.find("%m") != std::string::npos)
				finalMsg.replace(finalMsg.find("%m"), 2, message);

			std::cout << finalMsg << "\n";
		}

		void SetPattern(std::string pattern) { m_Pattern = pattern; }
	private:
		std::string m_Pattern = "[%s] %t: %m";
	};
}