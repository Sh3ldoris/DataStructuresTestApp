#pragma once
#include "TestInfo.h"

class Test
{
public:
	virtual TestInfo runTest(char scenario, TestInfo &info) = 0;
	virtual void getScenarios(char* scenarios) = 0;
};

