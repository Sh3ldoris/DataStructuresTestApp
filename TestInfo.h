#pragma once
class TestInfo
{
public:
	void setOperationsCount(int count);
	int getOperationsCount();

	void setOperationsTime(float time);
	float getOperationsTime();

private:
	int operationCount = 0;
	float operationTime = 0;
};

