#pragma once
#include <string>
class TestInfo
{
public:
	void setMessage(std::string message);
	std::string getMessage();
	void setOperationsTime(float time);
	float getOperationsTime();

private:
	std::string message = "";
	float operationTime = 0;
	
};

