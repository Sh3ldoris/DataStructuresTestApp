#include "TestInfo.h"

void TestInfo::setOperationsCount(int count)
{
	operationCount = count;
}

int TestInfo::getOperationsCount()
{
	return operationCount;
}

void TestInfo::setOperationsTime(float time)
{
	operationTime = time;
}

float TestInfo::getOperationsTime()
{
	return operationTime;
}
