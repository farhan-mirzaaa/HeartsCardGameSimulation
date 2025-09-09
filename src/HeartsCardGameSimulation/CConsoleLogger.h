#pragma once
#include <memory>
#include <iostream>

class CConsoleLogger
{
private:
	CConsoleLogger();
public:
	CConsoleLogger(const CConsoleLogger&) = delete;
	CConsoleLogger(CConsoleLogger&&) = delete;
	CConsoleLogger& operator=(const CConsoleLogger&) = delete;
	CConsoleLogger& operator=(CConsoleLogger&&) = delete;

	static std::shared_ptr<CConsoleLogger> GetInstance();

	void PrintString(std::string logString, bool addNewLine = true);
};

