#include "shlog.h"

int main() {
	shlog::ConsoleLogger logger;

	logger.SetPattern("%c[%su] %d %t: %m");

	logger.Trace("This is a test");
	logger.Info("This is a test");
	logger.Warn("This is a test");
	logger.Error("This is a test");
	logger.Critical("This is a test");
}