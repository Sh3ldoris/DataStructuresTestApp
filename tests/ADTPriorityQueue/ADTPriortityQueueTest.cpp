#include "ADTPriortityQueueTest.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <chrono> 
#include <sstream>
#include <fstream>

#include "../../structures/priority_queue/priority_queue_sorted_array_list.h"
#include "../../structures/priority_queue/priority_queue_two_lists.h"
#include "../../structures/priority_queue/heap.h"

using namespace std;
using namespace structures;

ADTPriortityQueueTest::ADTPriortityQueueTest():
	fileWriter(new FileOutputHander()),
	scenarios("ABC")
{
	srand(time(NULL));
}

ADTPriortityQueueTest::~ADTPriortityQueueTest()
{
	delete fileWriter;
	fileWriter = nullptr;
}

void ADTPriortityQueueTest::runTest(char scenario, TestInfo& info)
{
	//Measure for test length 
	tp t0;
	tp t1;
	t0 = clck::now();

	switch (scenario)
	{
	case 'A':
		setTestScenarioOperationRanges(35, 35, 30);
		break;
	case 'B':
		setTestScenarioOperationRanges(50, 30, 20);
		break;
	case 'C':
		setTestScenarioOperationRanges(70, 25, 5);
		break;
	default:
		info.setOperationsTime(0);
		info.setMessage("");
		return;
	}

	PriorityQueueSortedArrayList<int> pqsal;
	//PriorityQueueTwoLists<int> pqtl;
	Heap<int> heap;

	string fileName = baseDir;
	fileName.append("/ADTPQList-");
	fileName.push_back(scenario);
	fileName.append(".csv");

	fileWriter->openFile(fileName, "trunc");

	runTestForImplementation(pqsal, "PQSAL");
	runTestForImplementation(heap, "HEAP");
	//runTestForImplementation(pqtl, "PQTL");

	fileWriter->closeFile();

	t1 = clck::now();
	duration ot = t1 - t0;
	ms finalTime = std::chrono::duration_cast<ms>(ot);

	ostringstream s;
	s << "\tPocet vykonanych operacii pre HEAP: " << heapOpCount << endl;
	s << "\tPocet vykonanych operacii pre PQSAL: " << pqsalOpCount << endl;
	//s << "\tPocet vykonanych operacii pre PQTL: " << pqtlOpCount << endl;
	info.setMessage(s.str());
	info.setOperationsTime((float)finalTime.count() / 1000000);
}

std::string ADTPriortityQueueTest::getScenarios()
{
	return scenarios;
}

void ADTPriortityQueueTest::setTestScenarioOperationRanges(int insertRange, int removeRange, int getRange)
{
	if (insertRange < 0 ||
		removeRange < 0 ||
		getRange < 0 ||
		(insertRange + removeRange + getRange) != 100
		)
	{
		return;
	}

	this->insertRange = insertRange;
	this->removeRange = removeRange;
	this->getRange = getRange;
}

void ADTPriortityQueueTest::runTestForImplementation(structures::PriorityQueue<int>& queue, std::string implName)
{
	string operation = ""; //just empty ""
	for (int i = 0; i < operationsCount; i++)
	{
		int rnd = rand() % 100;
		float opTime = -1;

		if (rnd < insertRange)
		{
			opTime = insertOperation(queue);
			if (opTime > -1.0)
			{
				fileWriter->writeRecord(implName, "insert", operation, queue.size() - 1, opTime);
			}
		}
		else if (rnd < removeRange + insertRange)
		{
			opTime = removeOperation(queue);
			if (opTime > -1.0)
			{
				fileWriter->writeRecord(implName, "remove", operation, queue.size() + 1, opTime);
			}
		}
		else
		{
			opTime = getOperation(queue);
			if (opTime > -1.0)
			{
				fileWriter->writeRecord(implName, "get", operation, queue.size(), opTime);
			}
		}

		if (opTime > -1)
		{
			if (implName == "HEAP") { heapOpCount++; }
			else if (implName == "PQTL") { pqtlOpCount++; }
			else { pqsalOpCount++; }
		}
	}
}

float ADTPriortityQueueTest::insertOperation(structures::PriorityQueue<int>& queue)
{
	int value = rand();
	int priority = rand() % 10001;
	tp t0;
	tp t1;

	t0 = clck::now();
	queue.push(priority, value);
	t1 = clck::now();

	duration ot = t1 - t0;
	ms finalTime = std::chrono::duration_cast<ms>(ot);

	return finalTime.count();
}

float ADTPriortityQueueTest::removeOperation(structures::PriorityQueue<int>& queue)
{
	if (queue.size() == 0)
	{
		return -1.0;
	}

	tp t0;
	tp t1;
	t0 = clck::now();
	int item = queue.pop();
	t1 = clck::now();

	duration ot = t1 - t0;
	ms finalTime = std::chrono::duration_cast<ms>(ot);
	return finalTime.count();
}

float ADTPriortityQueueTest::getOperation(structures::PriorityQueue<int>& queue)
{
	if (queue.size() == 0)
	{
		return -1.0;
	}

	tp t0;
	tp t1;
	t0 = clck::now();
	int item = queue.peek();
	t1 = clck::now();

	duration ot = t1 - t0;
	ms finalTime = std::chrono::duration_cast<ms>(ot);
	return finalTime.count();
}
