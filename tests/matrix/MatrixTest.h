#pragma once
#include "../../Test.h"
#include "../../FileOutputHander.h"
#include "../../structures/matrix/Matrix.h"

#include <string>
#include <chrono> 
#include <time.h>
#include <utility>  
#include <vector>

typedef std::chrono::high_resolution_clock clck;
typedef std::chrono::microseconds ms;
typedef std::chrono::duration<float> duration;
typedef std::chrono::high_resolution_clock::time_point tp;

class MatrixTest : public Test
{
public:
    MatrixTest();
    ~MatrixTest();
    void runTest(char scenario, TestInfo& info) override;
    std::string getScenarios() override;
private:
    void runScenarioA();
    void runScenarioB();
    void matrixAddition(mystruct::Matrix<int>& m1, mystruct::Matrix<int>& m2, mystruct::Matrix<int>& result);
    void matrixMultiplication(mystruct::Matrix<int>& m1, mystruct::Matrix<int>& m2, mystruct::Matrix<int>& result);

private:
    int maxSize;
    int sizeAddition;
    int repetitions;
    std::string scenarios;
    std::string baseDir = "CSV-DATA";
    FileOutputHander* fileWriter;
};

