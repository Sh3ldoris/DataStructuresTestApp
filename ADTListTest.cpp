#include "ADTListTest.h"
#include <iostream>

using namespace std;

ADTListTest::ADTListTest():
	fileWriter(new FileOutputHander()),
	scenarios("ABC")
{
}

ADTListTest::~ADTListTest()
{
	delete fileWriter;
	fileWriter = nullptr;
}

void ADTListTest::runTest(char scenario, TestInfo& info)
{
	info.setOperationsCount(10000000);
	info.setOperationsTime(42.34);
}

const char* ADTListTest::getScenarios() const
{
	return scenarios;
}
