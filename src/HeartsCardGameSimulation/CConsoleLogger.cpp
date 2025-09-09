#include "CConsoleLogger.h"

CConsoleLogger::CConsoleLogger()
{}

std::shared_ptr<CConsoleLogger> CConsoleLogger::GetInstance()
{
	static std::shared_ptr<CConsoleLogger> singleInstance(new CConsoleLogger());
	return singleInstance;
}

void CConsoleLogger::PrintString(std::string logString, bool addNewLine)
{
	if (addNewLine)
		std::cout << logString << std::endl;
	else
		std::cout << logString;
}
