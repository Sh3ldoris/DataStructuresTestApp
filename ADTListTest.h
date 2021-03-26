#pragma once
#include <string>
#include <chrono> 
#include <time.h>
#include <utility>  
#include <vector>

#include "Test.h"
#include "FileOutputHander.h"
#include "structures/list/list.h"

typedef std::chrono::high_resolution_clock clck;
typedef std::chrono::microseconds ms;
typedef std::chrono::duration<float> duration;
typedef std::chrono::high_resolution_clock::time_point tp;

class ADTListTest : public Test
{
public:
    void runTest(char scenario, TestInfo& info);
    std::string getScenarios();
    ADTListTest();
    ~ADTListTest();

private:
    void setTestScenarioOperationRanges(int insertRange, int removeRange, int getRange, int indexRange);
    void runTestForImplementation(structures::List<int>& list, std::string implName);
    float insertOperation(structures::List<int>& list);
    float removeOperation(structures::List<int>& list);
    float getOperation(structures::List<int>& list);
    float indexOperation(structures::List<int>& list);

private:
    char* scenarios;
    std::string sscenarios = "";
    std::vector<std::pair<std::string, std::vector<int>>> data{};
    FileOutputHander* fileWriter;
    int insertRange, removeRange, getRange, indexRange = 0;
    int operationsCount = 100;
    std::string baseDir = "CSV-DATA";
};

