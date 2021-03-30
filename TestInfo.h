#pragma once
#include <string>
class TestInfo
{
public:
	void setMessage(std::string message);
	std::string getMessage();

	void setOperationsCount(int count);
	int getOperationsCount();

	void setOperationsTime(float time);
	float getOperationsTime();

private:
	std::string message = "";
	int operationCount = 0;
	float operationTime = 0;
	
};

