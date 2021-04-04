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
    maxSize(2000),
    sizeAddition(100),
    repetitions(10),
    fixedLength(5)
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
    string rawInput;
    int fixSize = -1, sizeAdd = -1;
    cout << "Zadajte parametre pre Matrix - test\n";
    cout << "Hodnota pevnej casti matice (variabilna je (0;2000>): ";
    cin >> rawInput;
    if (cin.fail()) {
        cin.clear();
        cin.ignore();
        rawInput.clear();
        rawInput = "";
        fixSize = -1;
    }
    else {
        fixSize = atoi(rawInput.c_str());
    }
    while (rawInput == "" || fixSize <= 0 || fixSize > 2000)
    {
        onceAgainSelection(fixSize, rawInput);
    }

    cout << "Hodnota casti ktora sa bude pripocitavat: ";
    cin >> rawInput;
    if (cin.fail()) {
        cin.clear();
        cin.ignore();
        rawInput.clear();
        rawInput = "";
        sizeAdd = -1;
    }
    else {
        sizeAdd = atoi(rawInput.c_str());
    }
    while (rawInput == "" || sizeAdd <= 0 || sizeAdd > 2000)
    {
        onceAgainSelection(sizeAdd, rawInput);
    }

    fixedLength = fixSize;
    sizeAddition = sizeAdd;

    tp t0;
    tp t1;
    t0 = clck::now();

    switch (scenario)
    {
    case 'A':
        runScenarioA();
        break;

    case 'B':
        runScenarioB();
        break;

    default:
        break;
    }

    t1 = clck::now();
    duration ot = t1 - t0;
    ms finalTime = std::chrono::duration_cast<ms>(ot);
    info.setMessage("\tTest matic prebehol uspesne!\n");
    info.setOperationsTime((float)finalTime.count() / 1000000);
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

    for (int i = 1; i < maxSize; i += sizeAddition)
    {
        /************ vytvorit matice ***************/
        CoherentMatrix<int> cm1(fixedLength, i);
        cm1.setValues(1);
        CoherentMatrix<int> cm2(fixedLength, i);
        cm2.setValues(2);
        CoherentMatrix<int> cmResult1(fixedLength, i);
        cmResult1.setValues(0);
        float avrgTime1 = 0;

        CoherentMatrix<int> cm3(i, fixedLength);
        cm3.setValues(1);
        CoherentMatrix<int> cm4(i, fixedLength);
        cm4.setValues(2);
        CoherentMatrix<int> cmResult2(i, fixedLength);
        cmResult2.setValues(0);
        float avrgTime2 = 0;

        for (int j = 0; j < repetitions; j++)
        {
            t0 = clck::now();
            matrixAddition(cm1, cm2, cmResult1);
            t1 = clck::now();

            duration ot = t1 - t0;
            ms finalTime = std::chrono::duration_cast<ms>(ot);
            avrgTime1 += finalTime.count();

            t0 = clck::now();
            matrixAddition(cm3, cm4, cmResult2);
            t1 = clck::now();

            ot = t1 - t0;
            finalTime = std::chrono::duration_cast<ms>(ot);
            avrgTime2 += finalTime.count();
        }

        //Zapisat do suboru prislusny record
        s << "CM" << ';' << cmResult1.getColumnLength() << ';' << cmResult1.getRowLength() << ';' << avrgTime1 / repetitions;
        record.clear();
        record = s.str();
        s.str("");
        s.clear();
        fileWriter->writeLine(record);

        //Zapisat do suboru prislusny record
        s << "CM" << ';' << cmResult2.getColumnLength() << ';' << cmResult2.getRowLength() << ';' << avrgTime2 / repetitions;
        record.clear();
        record = s.str();
        s.str("");
        s.clear();
        fileWriter->writeLine(record);
    }

    for (int i = 1; i < maxSize; i += sizeAddition)
    {
        /************ vytvorit matice ***************/
        IncoherentMatrix<int> cm1(fixedLength, i);
        cm1.setValues(1);
        IncoherentMatrix<int> cm2(fixedLength, i);
        cm2.setValues(2);
        IncoherentMatrix<int> cmResult1(fixedLength, i);
        cmResult1.setValues(0);
        float avrgTime1 = 0;

        IncoherentMatrix<int> cm3(i, fixedLength);
        cm3.setValues(1);
        IncoherentMatrix<int> cm4(i, fixedLength);
        cm4.setValues(2);
        IncoherentMatrix<int> cmResult2(i, fixedLength);
        cmResult2.setValues(0);
        float avrgTime2 = 0;

        for (int j = 0; j < repetitions; j++)
        {
            t0 = clck::now();
            matrixAddition(cm1, cm2, cmResult1);
            t1 = clck::now();

            duration ot = t1 - t0;
            ms finalTime = std::chrono::duration_cast<ms>(ot);
            avrgTime1 += finalTime.count();

            t0 = clck::now();
            matrixAddition(cm3, cm4, cmResult2);
            t1 = clck::now();

            ot = t1 - t0;
            finalTime = std::chrono::duration_cast<ms>(ot);
            avrgTime2 += finalTime.count();
        }

        //Zapisat do suboru prislusny record
        s << "IM" << ';' << cmResult1.getColumnLength() << ';' << cmResult1.getRowLength() << ';' << avrgTime1 / repetitions;
        record.clear();
        record = s.str();
        s.str("");
        s.clear();
        fileWriter->writeLine(record);

        //Zapisat do suboru prislusny record
        s << "IM" << ';' << cmResult2.getColumnLength() << ';' << cmResult2.getRowLength() << ';' << avrgTime2 / repetitions;
        record.clear();
        record = s.str();
        s.str("");
        s.clear();
        fileWriter->writeLine(record);
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

    for (int i = 1; i < maxSize; i += sizeAddition)
    {
        /************ vytvorit matice ***************/
        CoherentMatrix<int> cm1(fixedLength, i);
        cm1.setValues(rand());
        CoherentMatrix<int> cm2(i, fixedLength);
        cm2.setValues(rand());
        CoherentMatrix<int> cmResult1(fixedLength, fixedLength);
        cmResult1.setValues(0);
        float avrgTime1 = 0;

        CoherentMatrix<int> cm3(i, fixedLength);
        cm3.setValues(rand());
        CoherentMatrix<int> cm4(fixedLength, i);
        cm4.setValues(rand());
        CoherentMatrix<int> cmResult2(i, i);
        cmResult2.setValues(0);
        float avrgTime2 = 0;

        for (int j = 0; j < repetitions; j++)
        {
            t0 = clck::now();
            matrixMultiplication(cm1, cm2, cmResult1);
            t1 = clck::now();

            duration ot = t1 - t0;
            ms finalTime = std::chrono::duration_cast<ms>(ot);
            avrgTime1 += finalTime.count();

            t0 = clck::now();
            matrixMultiplication(cm3, cm4, cmResult2);
            t1 = clck::now();

            ot = t1 - t0;
            finalTime = std::chrono::duration_cast<ms>(ot);
            avrgTime2 += finalTime.count();
        }

        //Zapisat do suboru prislusny record
        s << "CM" << ';' << cm1.getColumnLength() << ';' << cm1.getRowLength() << ';' << avrgTime1 / repetitions;
        record.clear();
        record = s.str();
        s.str("");
        s.clear();
        fileWriter->writeLine(record);

        //Zapisat do suboru prislusny record
        s << "CM" << ';' << cm3.getColumnLength() << ';' << cm3.getRowLength() << ';' << avrgTime2 / repetitions;
        record.clear();
        record = s.str();
        s.str("");
        s.clear();
        fileWriter->writeLine(record);
    }

    for (int i = 1; i < maxSize; i += sizeAddition)
    {
        /************ vytvorit matice ***************/
        IncoherentMatrix<int> cm1(fixedLength, i);
        cm1.setValues(rand());
        IncoherentMatrix<int> cm2(i, fixedLength);
        cm2.setValues(rand());
        IncoherentMatrix<int> cmResult1(fixedLength, fixedLength);
        cmResult1.setValues(0);
        float avrgTime1 = 0;

        IncoherentMatrix<int> cm3(i, fixedLength);
        cm3.setValues(rand());
        IncoherentMatrix<int> cm4(fixedLength, i);
        cm4.setValues(rand());
        IncoherentMatrix<int> cmResult2(i, i);
        cmResult2.setValues(0);
        float avrgTime2 = 0;

        for (int j = 0; j < repetitions; j++)
        {
            t0 = clck::now();
            matrixMultiplication(cm1, cm2, cmResult1);
            t1 = clck::now();

            duration ot = t1 - t0;
            ms finalTime = std::chrono::duration_cast<ms>(ot);
            avrgTime1 += finalTime.count();

            t0 = clck::now();
            matrixMultiplication(cm3, cm4, cmResult2);
            t1 = clck::now();

            ot = t1 - t0;
            finalTime = std::chrono::duration_cast<ms>(ot);
            avrgTime2 += finalTime.count();
        }

        //Zapisat do suboru prislusny record
        s << "IM" << ';' << cm1.getColumnLength() << ';' << cm1.getRowLength() << ';' << avrgTime1 / repetitions;
        record.clear();
        record = s.str();
        s.str("");
        s.clear();
        fileWriter->writeLine(record);

        //Zapisat do suboru prislusny record
        s << "IM" << ';' << cm3.getColumnLength() << ';' << cm3.getRowLength() << ';' << avrgTime2 / repetitions;
        record.clear();
        record = s.str();
        s.str("");
        s.clear();
        fileWriter->writeLine(record);
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

void MatrixTest::onceAgainSelection(int& varToSelect, std::string& rawInput)
{
    cout << "\nSkuste to este raz: ";
    cin >> rawInput;
    if (cin.fail()) {
        cin.clear();
        cin.ignore();
        rawInput.clear();
        rawInput = "";
        varToSelect = -1;
    }
    else {
        varToSelect = atoi(rawInput.c_str());
    }
}

