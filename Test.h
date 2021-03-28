#pragma once
#include <string>

#include "TestInfo.h"

class Test
{
public:
	virtual void runTest(char scenario, TestInfo& info) = 0;
	virtual std::string getScenarios() = 0;
	virtual ~Test();
};

inline Test::~Test()
{
}