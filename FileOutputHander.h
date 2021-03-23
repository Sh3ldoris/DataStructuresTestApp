#pragma once
#include <string>
#include <fstream>

class FileOutputHander
{
public:
	void openFile(std::string filename);
	bool writeRecord(std::string structName, std::string operation, int itemsCount, float time);
	void closeFile();
	~FileOutputHander();

private: 
	std::ofstream file;
};

