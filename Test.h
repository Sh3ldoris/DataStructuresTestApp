#pragma once
#include "TestInfo.h"

class Test
{
public:
	virtual void runTest(char scenario, TestInfo& info) = 0;
	virtual const char* getScenarios() const = 0;
	virtual ~Test();
};

inline Test::~Test()
{
}