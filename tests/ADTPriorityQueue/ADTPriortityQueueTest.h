#pragma once
#include "../../Test.h"
#include "../../FileOutputHander.h"
#include "../../structures/priority_queue/priority_queue.h"

#include <string>
#include <chrono> 
#include <time.h>
#include <utility>  
#include <vector>

typedef std::chrono::high_resolution_clock clck;
typedef std::chrono::microseconds ms;
typedef std::chrono::duration<float> duration;
typedef std::chrono::high_resolution_clock::time_point tp;

class ADTPriortityQueueTest : public Test
{
public:
	ADTPriortityQueueTest();
	~ADTPriortityQueueTest();
	void runTest(char scenario, TestInfo& info) override;
	std::string getScenarios() override;

protected:
	void setTestScenarioOperationRanges(int insertRange, int removeRange, int getRange);
	void runTestForImplementation(structures::PriorityQueue<int>& queue, std::string implName);

private:
	float insertOperation(structures::PriorityQueue<int>& queue);
	float removeOperation(structures::PriorityQueue<int>& queue);
	float getOperation(structures::PriorityQueue<int>& queue);

protected:
	std::string baseDir = "CSV-DATA";
	FileOutputHander* fileWriter;
	int insertRange = 0;

private:
	std::string scenarios = "";
	int removeRange = 0, getRange = 0;
	int operationsCount = 100000;

	int heapOpCount = 0;
	int pqsalOpCount = 0;
	int pqtlOpCount = 0;
};

