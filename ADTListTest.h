#pragma once
#include "Test.h"
class ADTListTest :
    public Test
{
public:
    TestInfo runTest(char scenario, TestInfo& info);
    void getScenarios(char* scenarios);
};

