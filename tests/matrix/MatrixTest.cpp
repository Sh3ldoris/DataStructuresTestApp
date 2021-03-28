#include "MatrixTest.h"

#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <chrono> 
#include <sstream>
#include <fstream>
#include "../../structures/matrix/CoherentMatrix.h"
#include "../../structures/matrix/IncoherentMatrix.h"

using namespace std;
using namespace mystruct;

MatrixTest::MatrixTest() :
    fileWriter(new FileOutputHander()),
    scenarios("AB"),
    maxSize(1000),
    sizeAddition(100),
    repetitions(10)
{
    srand(time(NULL));
}

MatrixTest::~MatrixTest()
{
    delete fileWriter;
    fileWriter = nullptr;
}

void MatrixTest::runTest(char scenario, TestInfo& info)
{
    cout << "Matrix test ruuuun!\n";
    info.setOperationsCount(0);
    info.setOperationsTime(0);

    switch (scenario)
    {
    case 'A':
        runScenarioA();
        break;

    case 'B':
        maxSize =3;
        sizeAddition = 1;
        runScenarioB();
        break;

    default:
        break;
    }
}

std::string MatrixTest::getScenarios()
{
    return "AB";
}

void MatrixTest::runScenarioA()
{
    string fileName = baseDir;
    fileName.append("/Matrix-A");
    fileName.append(".csv");

    //Record ouput
    FileOutputHander foh;
    string record;
    ostringstream s;

    //Time output
    tp t0;
    tp t1;

    fileWriter->openFile(fileName, "trunc");

    for (int i = 1; i < maxSize + 1; i += sizeAddition)
    {
        for (int j = 1; j < maxSize + 1; j += sizeAddition)
        {
            /************ vytvorit matice ***************/
            CoherentMatrix<int> cm1(i, j);
            cm1.setValues(1);
            CoherentMatrix<int> cm2(i, j);
            cm2.setValues(2);
            CoherentMatrix<int> cmResult(i, j);
            cmResult.setValues(0);

            t0 = clck::now();
            matrixAddition(cm1, cm2, cmResult);
            t1 = clck::now();

            duration ot = t1 - t0;
            ms finalTime = std::chrono::duration_cast<ms>(ot);

            //Zapisat do suboru prislusny record
            s << "CM" << ';' << cmResult.getColumnLength() << ';' << cmResult.getRowLength() << ';' << finalTime.count();
            record.clear();
            record = s.str();
            s.str("");
            s.clear();
            fileWriter->writeLine(record);
        }
        cout << i << endl;
    }


    for (int i = 1; i < maxSize + 1; i += sizeAddition)
    {
        for (int j = 1; j < maxSize + 1; j += sizeAddition)
        {
            /************ vytvorit matice ***************/
            IncoherentMatrix<int> cm1(i, j);
            cm1.setValues(1);
            IncoherentMatrix<int> cm2(i, j);
            cm2.setValues(2);
            IncoherentMatrix<int> cmResult(i, j);
            cmResult.setValues(0);
            
            t0 = clck::now();
            matrixAddition(cm1, cm2, cmResult);
            t1 = clck::now();

            duration ot = t1 - t0;
            ms finalTime = std::chrono::duration_cast<ms>(ot);

            //Zapisat do suboru prislusny record
            s << "IM" << ';' << cmResult.getColumnLength() << ';' << cmResult.getRowLength() << ';' << finalTime.count();
            record.clear();
            record = s.str();
            s.str("");
            s.clear();
            fileWriter->writeLine(record);
        }
        cout << i << endl;
    }
    fileWriter->closeFile();
}

void MatrixTest::runScenarioB()
{
    string fileName = baseDir;
    fileName.append("/Matrix-B");
    fileName.append(".csv");

    //Record ouput
    FileOutputHander foh;
    string record;
    ostringstream s;

    //Time output
    tp t0;
    tp t1;

    fileWriter->openFile(fileName, "trunc");

    for (int i = 1; i < maxSize + 1; i += sizeAddition)
    {
        for (int j = 1; j < maxSize + 1; j += sizeAddition)
        {
            /************ vytvorit matice ***************/
            CoherentMatrix<int> cm1(i, j);
            cm1.setValues(1);
            CoherentMatrix<int> cm2(j, i);
            cm2.setValues(2);
            CoherentMatrix<int> cmResult(i, i);
            cmResult.setValues(0);

            t0 = clck::now();
            matrixMultiplication(cm1, cm2, cmResult);
            t1 = clck::now();

            duration ot = t1 - t0;
            ms finalTime = std::chrono::duration_cast<ms>(ot);

            //Zapisat do suboru prislusny record
            s << "CM" << ';' << cmResult.getColumnLength() << ';' << cmResult.getRowLength() << ';' << finalTime.count();
            record.clear();
            record = s.str();
            s.str("");
            s.clear();
            fileWriter->writeLine(record);
        }
        cout << i << endl;
    }


    for (int i = 1; i < maxSize + 1; i += sizeAddition)
    {
        for (int j = 1; j < maxSize + 1; j += sizeAddition)
        {
            /************ vytvorit matice ***************/
            IncoherentMatrix<int> cm1(i, j);
            cm1.setValues(1);
            IncoherentMatrix<int> cm2(j, i);
            cm2.setValues(2);
            IncoherentMatrix<int> cmResult(i, i);
            cmResult.setValues(0);

            t0 = clck::now();
            matrixMultiplication(cm1, cm2, cmResult);
            t1 = clck::now();

            duration ot = t1 - t0;
            ms finalTime = std::chrono::duration_cast<ms>(ot);

            //Zapisat do suboru prislusny record
            s << "IM" << ';' << cmResult.getColumnLength() << ';' << cmResult.getRowLength() << ';' << finalTime.count();
            record.clear();
            record = s.str();
            s.str("");
            s.clear();
            fileWriter->writeLine(record);
        }
        cout << i << endl;
    }
    fileWriter->closeFile();
}

void MatrixTest::matrixAddition(mystruct::Matrix<int>& m1, mystruct::Matrix<int>& m2, mystruct::Matrix<int>& result)
{
    for (int i = 0; i < result.getColumnLength(); i++)
    {
        for (int j = 0; j < result.getRowLength(); j++)
        {
            result.item(i, j) = m1.item(i, j) + m2.item(i, j);
        }
    }
}

void MatrixTest::matrixMultiplication(mystruct::Matrix<int>& m1, mystruct::Matrix<int>& m2, mystruct::Matrix<int>& result)
{
    for (int i = 0; i < m1.getColumnLength(); i++)
    {
        for (int j = 0; j < m1.getColumnLength(); j++)
        {
            int resultItem = 0;
            for (int k = 0; k < m1.getRowLength(); k++)
            {
                resultItem += m1.item(i, k) * m2.item(k, j);
            }
            result.item(i, j) = resultItem;
        }
    }
}

