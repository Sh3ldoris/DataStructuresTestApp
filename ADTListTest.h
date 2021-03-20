#pragma once
#include "Test.h"
#include "FileOutputHander.h"

class ADTListTest : public Test
{
public:
    void runTest(char scenario, TestInfo& info);
    const char* getScenarios() const;
    ADTListTest();
    ~ADTListTest();

private:
    const char* scenarios;
    FileOutputHander* fileWriter;
};

