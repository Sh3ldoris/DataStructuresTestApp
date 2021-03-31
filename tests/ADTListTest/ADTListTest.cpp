#include "ADTListTest.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <chrono> 
#include <sstream>
#include <fstream>

#include "../../structures/list/array_list.h"
#include "../../structures/list/linked_list.h"
#include "../../structures/list/CyclicLinkedList.h"

using namespace std;
using namespace structures;

ADTListTest::ADTListTest() :
	fileWriter(new FileOutputHander())
{
	srand(time(NULL));
}

ADTListTest::~ADTListTest()
{
	delete fileWriter;
	fileWriter = nullptr;
}

void ADTListTest::setTestScenarioOperationRanges(int insertRange, int removeRange, int getRange, int indexRange)
{
	if (insertRange < 0 || 
		removeRange < 0 || 
		getRange < 0 || 
		indexRange < 0 || 
		(insertRange + removeRange + getRange + indexRange) != 100
		)
	{
		return;
	}

	this->insertRange = insertRange;
	this->removeRange = removeRange;
	this->getRange = getRange;
	this->indexRange = indexRange;
}

void ADTListTest::runTestForImplementation(structures::List<int>& list, string implName)
{
	string operation = "";
	for (int i = 0; i < operationsCount; i++)
	{
		int rnd = rand() % 100;
		float opTime = -1;

		if (rnd < insertRange)
		{
			opTime = insertOperation(list, operation);
			if (opTime > -1.0)
			{
				fileWriter->writeRecord(implName, "insert", operation, list.size() - 1, opTime);
			}
			operation.clear();
		} 
		else if (rnd < removeRange + insertRange)
		{
			opTime = removeOperation(list, operation);
			if (opTime > -1.0)
			{
				fileWriter->writeRecord(implName, "remove", operation, list.size() + 1, opTime);
			}
			operation.clear();
		}
		else if (rnd < getRange + removeRange + insertRange)
		{
			opTime = getOperation(list, operation);
			if (opTime > -1.0)
			{
				fileWriter->writeRecord(implName, "get", operation, list.size(), opTime);
			}
			operation.clear();
		}
		else
		{
			opTime = indexOperation(list, operation);
			if (opTime > -1.0)
			{
				fileWriter->writeRecord(implName, "index", operation, list.size(), opTime);
			}
			operation.clear();
		}

		if (opTime > -1)
		{
			if (implName == "AL") { alOpCount++; }
			else if (implName == "LL") { llOpCount++; }
			else { cllOpCount++; }
		}
	}
}

float ADTListTest::insertOperation(structures::List<int>& list, std::string& operationName)
{
	int rnd = rand() % 3;
	int value = rand();
	int index;
	tp t0;
	tp t1;
	switch (rnd)
	{
	case 0:
		operationName = "insert-0";
		//cout << operationName << " - "<< list.size() << endl;
		t0 = clck::now();
		list.insert(value, 0);
		t1 = clck::now();
		break;
	case 1:
		operationName = "add";
		//cout << operationName << " - " << list.size() << endl;
		t0 = clck::now();
		list.add(value);
		t1 = clck::now();
		break;
	case 2:
		if (list.size() == 0)
		{
			index = 0;
		} else 
		{
			index = rand() % list.size();
		}
		operationName = "insert-i";
		//cout << operationName << " - " << list.size() << endl;
		t0 = clck::now();
		list.insert(value, index);
		t1 = clck::now();
		break;
	default:
		return -1.0;
	}
	duration ot = t1 - t0;
	ms finalTime = std::chrono::duration_cast<ms>(ot);
	return finalTime.count();
}

float ADTListTest::removeOperation(structures::List<int>& list, std::string& operationName)
{
	int a = list.size();
	// If there is no items in list thus cannot remove any item
	if (list.size() == 0)
	{
		return -1.0;
	}

	int rnd = rand() % 3;
	int index;
	tp t0;
	tp t1;
	switch (rnd)
	{
	case 0:
		operationName = "remove-0";
		//cout << operationName << " - " << list.size() << endl;
		t0 = clck::now();
		list.removeAt(0);
		t1 = clck::now();
		break;
	case 1:
		operationName = "remove-end";
		//cout << operationName << " - " << list.size() << endl;
		index = list.size() - 1;
		t0 = clck::now();
		list.removeAt(index);
		t1 = clck::now();
		break;
	case 2:
		operationName = "remove-i";
		//cout << operationName << " - " << list.size() << endl;
		index = rand() % list.size();
		t0 = clck::now();
		list.removeAt(index);
		t1 = clck::now();
		break;
	default:
		return -1.0;
	}
	duration ot = t1 - t0;
	ms finalTime = std::chrono::duration_cast<ms>(ot);
	return finalTime.count();
}

float ADTListTest::getOperation(structures::List<int>& list, std::string& operationName)
{
	// If there is no items in list thus cannot remove any item
	if (list.size() == 0)
	{
		return -1.0;
	}

	int rnd = rand() % 2;
	int index = rand() % list.size();
	int value = 0;
	tp t0;
	tp t1;
	switch (rnd)
	{
	case 0:
		operationName = "get-from-i";
		//cout << operationName << " - " << list.size() << endl;
		t0 = clck::now();
		value = list[index];
		t1 = clck::now();
		break;
	case 1:
		operationName = "set-on-i";
		//cout << operationName << " - " << list.size() << endl;
		value = rand();
		t0 = clck::now();
		list[index] = value;
		t1 = clck::now();
		break;
	default:
		return -1.0;
	}
	duration ot = t1 - t0;
	ms finalTime = std::chrono::duration_cast<ms>(ot);
	return finalTime.count();
}

float ADTListTest::indexOperation(structures::List<int>& list, std::string& operationName)
{
	// If there is no items in list thus cannot remove any item
	if (list.size() == 0)
	{
		return -1.0;
	}
	operationName = "index-of";
	//cout << operationName << " - " << list.size() << endl;
	int value = list[rand() % list.size()];
	auto t0 = clck::now();
	list.getIndexOf(value);
	auto t1 = clck::now();
	duration ot = t1 - t0;
	ms finalTime = std::chrono::duration_cast<ms>(ot);
	return finalTime.count();
}

void ADTListTest::runTest(char scenario, TestInfo& info)
{
	//Measure for test length 
	tp t0;
	tp t1;
	t0 = clck::now();

	int founded = -1;
	for (int i = 0; i < data.size(); i++)
	{
		if (data.at(i).first[0] == scenario)
		{
			int frstRange = data.at(i).second[0];
			int scndRange = data.at(i).second[1];
			int thrdRange = data.at(i).second[2];
			int frthRange = data.at(i).second[3];

			setTestScenarioOperationRanges(frstRange, scndRange, thrdRange, frthRange);
			founded = 1;
			break;
		}
	}

	if (founded == -1)
	{
		info.setOperationsCount(0);
		info.setOperationsTime(0);
		return;
	}

	//TODO: UI result
	
	ArrayList<int> al;
	LinkedList<int> ll;
	CyclicedLikedList<int> cll;

	string fileName = baseDir;
	fileName.append("/ADTList-");
	fileName.push_back(scenario);
	fileName.append(".csv");

	fileWriter->openFile(fileName, "trunc");

	runTestForImplementation(al, "AL");
	runTestForImplementation(ll, "LL");
	runTestForImplementation(cll, "CLL");

	fileWriter->closeFile();

	t1 = clck::now();
	duration ot = t1 - t0;
	ms finalTime = std::chrono::duration_cast<ms>(ot);

	ostringstream s;
	s << "\tPocet vykonanych operacii pre AL: " << alOpCount << endl;
	s << "\tPocet vykonanych operacii pre LL: " << llOpCount << endl;
	s << "\tPocet vykonanych operacii pre CLL: " << cllOpCount << endl;
	info.setMessage(s.str());
	info.setOperationsTime((float)finalTime.count() / 1000000);
}

string ADTListTest::getScenarios()
{
	sscenarios.clear();
	ifstream fin;
	fin.open("test.csv");
	string line, word;
	int isName = 0, index = 0, rangeValue = 0;
	while (fin.good()) {
		isName = 1;
		getline(fin, line);
		stringstream s(line);

		vector<int> ranges{};
		string sceanrioName = "";
		while (getline(s, word, ';')) {
			if (isName == 1)
			{
				sceanrioName.append(word);
				sscenarios.append(word);
				isName = -1;
			}
			else
			{
				rangeValue = stoi(word);
				ranges.push_back(rangeValue);
			}
		}
		data.push_back({ sceanrioName, ranges });
		index++;
	}
	return sscenarios;
}
