#pragma once
#include "../ADTPriortityQueueTest.h"
#include "../../../structures/priority_queue/TwoListsImpl/PriorityQueueTwoListsConst.h"
#include "../../../structures/priority_queue/TwoListsImpl/PriorityQueueTwoListsHalf.h"
#include <string>
#include <iostream>

using namespace std;
using namespace structures;

class BonusPQTests : public ADTPriortityQueueTest
{
public:	
	void runTest(char scenario, TestInfo& info) override;
};

void BonusPQTests::runTest(char scenario, TestInfo& info)
{
	//Measure for test length 
	tp t0;
	tp t1;
	t0 = clck::now();

	switch (scenario)
	{
	case 'A':
		this->setTestScenarioOperationRanges(35, 35, 30);
		break;
	case 'B':
		this->setTestScenarioOperationRanges(50, 30, 20);
		break;
	case 'C':
		this->setTestScenarioOperationRanges(70, 25, 5);
		break;
	default:
		info.setOperationsTime(0);
		info.setMessage("");
		return;
	}

	PriorityQueueTwoLists<int> pqtl;
	PriorityQueueTwoListsConst<int> constPQ((int)100000 /this->insertRange);
	PriorityQueueTwoListsHalf<int> halfPQ;

	string fileName = this->baseDir;
	fileName.append("/ADTPQTwoListImpl-");
	fileName.push_back(scenario);
	fileName.append(".csv");

	this->fileWriter->openFile(fileName, "trunc");


	runTestForImplementation(pqtl, "PQTL");
	this->runTestForImplementation(halfPQ, "halfPQTL");
	this->runTestForImplementation(constPQ, "constPQTL");

	this->fileWriter->closeFile();

	t1 = clck::now();
	duration ot = t1 - t0;
	ms finalTime = std::chrono::duration_cast<ms>(ot);

	ostringstream s;
	info.setMessage(s.str());
	info.setOperationsTime((float)finalTime.count() / 1000000);
}