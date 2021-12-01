#include "shlog.h"

int main() {
	shlog::ConsoleLogger logger;

	logger.SetPattern("(%t) %m");

	logger.Log("Test");
}