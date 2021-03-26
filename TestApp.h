#pragma once
#include <string>
#include "Test.h"
#include "TestInfo.h"

class TestApp
{
public:
	TestApp();
	~TestApp();
	void run();

private:
	bool initializeTest(int testSelection);
	bool addNewADTScenatio();
	void onceAgainSelection(int& varToSelect);
	void onceAgainSelection(char& varToSelect, std::string& rawInput);
	void printStructTestSelection();
	void printScenarioSelection();
	void printConfirmation();
	void printTestResults();

private:
	TestInfo* info;
	Test* test;
	std::string selectedTest;
	std::string scenarios;
	std::string message;
	int testSelection = -1, scenarioSelection = -1, confirmSelection = -1;
};

