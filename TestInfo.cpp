#include "TestInfo.h"

void TestInfo::setMessage(std::string message)
{
	this->message = message;
}

std::string TestInfo::getMessage()
{
	return message;
}

void TestInfo::setOperationsTime(float time)
{
	operationTime = time;
}

float TestInfo::getOperationsTime()
{
	return operationTime;
}
