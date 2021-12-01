#include "shlog.h"

int main() {
	shlog::ConsoleLogger logger;

	logger.SetPattern("[%s] %t: %m");

	logger.Info("Error");
}