#pragma once

#include <iostream>

#include <string>
#include <sstream>

#include <chrono>
#include <iomanip>

/*
	Pattern Keys:
	%t = Current time
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

	class ConsoleLogger {
	public:
		void Log(std::string message) {
			std::string finalMsg = m_Pattern;

			if (finalMsg.find("%m") != std::string::npos)
				finalMsg.replace(finalMsg.find("%m"), 2, message);
			if (finalMsg.find("%t") != std::string::npos)
				finalMsg.replace(finalMsg.find("%t"), 2, GetCurrentTime());

			std::cout << finalMsg << "\n";
		}
		void SetPattern(std::string pattern) { m_Pattern = pattern; }
	private:
		std::string m_Pattern = "[%t] %m";
	};
}