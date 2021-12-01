#pragma once

#include <iostream>

#include <string>
#include <sstream>

#include <algorithm>
#include <cctype>

#include <chrono>
#include <iomanip>

#include <windows.h>

/*
	Pattern Keys:
	%t  = Current time (eg. 01:20:03)
	%d  = Current date (eg. 2021-2-21)
	%a  = Current day name (eg. Wednesday)
	%a  = Current day name abbreviated (eg. Wed)
	%b  = Current month name (eg. August)
	%ba = Current month name abbreviated (eg. Aug)
	%tz = Timezone difference (eg. +1100)

	%s  = Severity (eg. Warn, Info)
	%sl = Severity lowercase(eg. warn, info)
	%su = Severity uppercase(eg. WARN, INFO)

	%c  = Severity color
	%m  = Message 
*/

namespace shlog {
	std::string GetCurrentTimeAsString(std::string format = "%H:%M:%S") {
		auto t = std::time(nullptr);
		auto tm = *std::localtime(&t);

		std::ostringstream oss;
		oss << std::put_time(&tm, format.c_str());
		return oss.str();
	}

	std::string ToLower(std::string data) {
		std::string returnStr;
		for (auto& c : data)
		{
			returnStr += tolower(c);
		}
		return returnStr;
	}

	std::string ToUpper(std::string data) {
		std::string returnStr;
		for (auto& c : data)
		{
			returnStr += toupper(c);
		}
		return returnStr;
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
		case shlog::Trace: return "Trace";
		case shlog::Info: return "Info";
		case shlog::Warn: return "Warn";
		case shlog::Error: return "Error";
		case shlog::Critical: return "Critical";
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

			if (finalMsg.find("%d") != std::string::npos)
				finalMsg.replace(finalMsg.find("%d"), 2, GetCurrentTimeAsString("%Y-%m-%d"));
			if (finalMsg.find("%aa") != std::string::npos)
				finalMsg.replace(finalMsg.find("%aa"), 3, GetCurrentTimeAsString("%a"));
			if (finalMsg.find("%a") != std::string::npos)
				finalMsg.replace(finalMsg.find("%a"), 2, GetCurrentTimeAsString("%A"));
			if (finalMsg.find("%ba") != std::string::npos)
				finalMsg.replace(finalMsg.find("%ba"), 3, GetCurrentTimeAsString("%b"));
			if (finalMsg.find("%b") != std::string::npos)
				finalMsg.replace(finalMsg.find("%b"), 2, GetCurrentTimeAsString("%B"));
			if (finalMsg.find("%tz") != std::string::npos)
				finalMsg.replace(finalMsg.find("%tz"), 3, GetCurrentTimeAsString("%z"));
			if (finalMsg.find("%t") != std::string::npos)
				finalMsg.replace(finalMsg.find("%t"), 2, GetCurrentTimeAsString());

			if (finalMsg.find("%sl") != std::string::npos)
				finalMsg.replace(finalMsg.find("%sl"), 3, ToLower(LogTypeToString(type)));
			if (finalMsg.find("%su") != std::string::npos)
				finalMsg.replace(finalMsg.find("%su"), 3, ToUpper(LogTypeToString(type)));
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