#include "ADTListTest.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <chrono> 
#include <thread>

#include "structures/list/array_list.h"
#include "structures/list/linked_list.h"

using namespace std;
using namespace structures;

ADTListTest::ADTListTest():
	fileWriter(new FileOutputHander()),
	scenarios("ABC")
{
	srand(time(NULL));
}

ADTListTest::~ADTListTest()
{
	delete fileWriter;
	fileWriter = nullptr;
}

void ADTListTest::setTestScenarioOperationRanges(int insertRange, int removeRange, int getRange, int indexRange)
{
	if (insertRange < 0 || 
		removeRange < 0 || 
		getRange < 0 || 
		indexRange < 0 || 
		(insertRange + removeRange + getRange + indexRange) != 100
		)
	{
		return;
	}

	this->insertRange = insertRange;
	this->removeRange = removeRange;
	this->getRange = getRange;
	this->indexRange = indexRange;
}

void ADTListTest::runTestForImplementation(structures::List<int>& list, string implName)
{

	for (int i = 0; i < operationsCount; i++)
	{
		int rnd = rand() % 100;
		float opTime = -1;

		if (rnd < insertRange)
		{
			opTime = insertOperation(list);
			if (opTime > -1.0)
			{
				fileWriter->writeRecord(implName, "insert", list.size() - 1, opTime);
			}
		} 
		else if (rnd < removeRange + insertRange)
		{
			opTime = removeOperation(list);
			if (opTime > -1.0)
			{
				fileWriter->writeRecord(implName, "remove", list.size() + 1, opTime);
			}
		}
		else if (rnd < getRange + removeRange + insertRange)
		{
			opTime = getOperation(list);
			if (opTime > -1.0)
			{
				fileWriter->writeRecord(implName, "get", list.size(), opTime);
			}
		}
		else
		{
			opTime = indexOperation(list);
			if (opTime > -1.0)
			{
				fileWriter->writeRecord(implName, "index", list.size(), opTime);
			}
		}
	}
}

float ADTListTest::insertOperation(structures::List<int>& list)
{
	int rnd = rand() % 3;
	int value = rand();
	int index;
	tp t0;
	tp t1;
	switch (rnd)
	{
	case 0:
		t0 = clck::now();
		list.insert(value, 0);
		t1 = clck::now();
		break;
	case 1:
		t0 = clck::now();
		list.add(value);
		t1 = clck::now();
		break;
	case 2:
		if (list.size() == 0)
		{
			index = 0;
		} else 
		{
			index = rand() % list.size();
		}
		t0 = clck::now();
		list.insert(value, index);
		t1 = clck::now();
		break;
	default:
		return -1.0;
	}
	cout << "insert - ";
	duration ot = t1 - t0;
	ms finalTime = std::chrono::duration_cast<ms>(ot);
	cout << finalTime.count() << "\n";
	return finalTime.count();
}

float ADTListTest::removeOperation(structures::List<int>& list)
{
	int a = list.size();
	// If there is no items in list thus cannot remove any item
	if (list.size() == 0)
	{
		return -1.0;
	}

	int rnd = rand() % 3;
	int index;
	tp t0;
	tp t1;
	switch (rnd)
	{
	case 0:
		t0 = clck::now();
		list.removeAt(0);
		t1 = clck::now();
		break;
	case 1:
		index = list.size() - 1;
		t0 = clck::now();
		list.removeAt(index);
		t1 = clck::now();
		break;
	case 2:
		index = rand() % list.size();
		t0 = clck::now();
		list.removeAt(index);
		t1 = clck::now();
		break;
	default:
		return -1.0;
	}
	cout << "remove - ";
	duration ot = t1 - t0;
	ms finalTime = std::chrono::duration_cast<ms>(ot);
	cout << finalTime.count() << "\n";
	return finalTime.count();
}

float ADTListTest::getOperation(structures::List<int>& list)
{
	// If there is no items in list thus cannot remove any item
	if (list.size() == 0)
	{
		return -1.0;
	}

	int rnd = rand() % 2;
	int index = rand() % list.size();
	int value = 0;
	tp t0;
	tp t1;
	switch (rnd)
	{
	case 0:
		t0 = clck::now();
		value = list[index];
		t1 = clck::now();
		break;
	case 1:
		t0 = clck::now();
		list[index] = index;
		t1 = clck::now();
		break;
	default:
		return -1.0;
	}
	cout << "get - ";
	duration ot = t1 - t0;
	ms finalTime = std::chrono::duration_cast<ms>(ot);
	cout << finalTime.count() << "\n";
	return finalTime.count();
}

float ADTListTest::indexOperation(structures::List<int>& list)
{
	// If there is no items in list thus cannot remove any item
	if (list.size() == 0)
	{
		return -1.0;
	}
	int value = list[rand() % list.size()];
	auto t0 = clck::now();
	list.getIndexOf(value);
	auto t1 = clck::now();
	cout << "index - ";
	duration ot = t1 - t0;
	ms finalTime = std::chrono::duration_cast<ms>(ot);
	cout << finalTime.count() << "\n";
	return finalTime.count();
}

void ADTListTest::runTest(char scenario, TestInfo& info)
{
	switch (scenario)
	{
	case 'A':
		setTestScenarioOperationRanges(20, 20, 50, 10);
		break;
	case 'B':
		setTestScenarioOperationRanges(35, 35, 20, 10);
		break;
	case 'C':
		setTestScenarioOperationRanges(45, 45, 5, 5);
		break;
	default:
		info.setOperationsCount(0);
		info.setOperationsTime(0);
		return;
	}

	info.setOperationsCount(11110);
	info.setOperationsTime(34.12);
	
	ArrayList<int> al;
	LinkedList<int> ll;

	string fileName = baseDir;
	fileName.append("/ADTList-");
	fileName.push_back(scenario);
	fileName.append(".csv");

	fileWriter->openFile(fileName);

	runTestForImplementation(al, "AL");
	runTestForImplementation(ll, "LL");

	fileWriter->closeFile();
	
}

const char* ADTListTest::getScenarios() const
{
	return scenarios;
}
