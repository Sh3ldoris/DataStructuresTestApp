#include "FileOutputHander.h"
#include <iostream>

void FileOutputHander::openFile(std::string filename)
{
	if (filename.size() > 0)
	{
		file.open(filename, std::fstream::out | std::fstream::trunc);
	}
}

bool FileOutputHander::writeRecord(std::string structName, std::string operation, int itemsCount, float time)
{
	if (!file.is_open())
	{
		return false;
	}

	file << structName << ";" << operation << ";" << itemsCount << ";" << time << std::endl;
	return true;
}

void FileOutputHander::closeFile()
{
	if (file.is_open())
	{
		file.close();
	}
}

FileOutputHander::~FileOutputHander()
{
	this->closeFile();
}
