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
	void onceAgainSelection(int& varToSelect);

private:
	TestInfo* info;
	Test* test;
	std::string selectedTest;
};

