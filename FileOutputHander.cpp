#include "FileOutputHander.h"
#include <iostream>
#include <string>

void FileOutputHander::openFile(std::string filename, std::string mode)
{
	if (filename.size() <= 0)
	{
		return;
	}
	if (mode == "trunc")
	{
		file.open(filename, std::fstream::out | std::fstream::trunc);
		return;
	}
	if (mode == "app")
	{
		file.open(filename, std::fstream::out | std::fstream::app);
		return;
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

bool FileOutputHander::writeLine(std::string line)
{
	if (!file.is_open())
	{
		return false;
	}

	file << line << std::endl;
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
