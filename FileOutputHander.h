#pragma once
#include <string>
#include <fstream>
#include <string>

class FileOutputHander
{
public:
	void openFile(std::string filename, std::string mode);
	bool writeRecord(std::string structName, std::string operationGroup, std::string operation, int itemsCount, float time);
	bool writeLine(std::string line);
	void closeFile();
	~FileOutputHander();

private: 
	std::ofstream file;
};

