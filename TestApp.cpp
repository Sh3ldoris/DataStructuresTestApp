#include "TestApp.h"
#include "tests/ADTListTest/ADTListTest.h"
#include "tests/ADTPriorityQueue/ADTPriortityQueueTest.h"
#include "tests/Matrix/MatrixTest.h"
#include "structures/list/list.h"
#include "structures/list/array_list.h"
#include "FileOutputHander.h"

#include <iostream>
#include <sstream>

using namespace structures;
using namespace std;

TestApp::TestApp():
	info(new TestInfo()),
	test(nullptr),
	message("")
{
}

TestApp::~TestApp()
{
	cout << "Aplikacia bola ukocena!\n";
	delete test;
	test = nullptr;
	delete info;
	info = nullptr;
}

void TestApp::run()
{
	/********** Test type selection **********/
	printStructTestSelection();

	system("cls");
	message.append("=> Test : ");
	message.append(selectedTest);


	/********** Test scenario selection **********/
	printScenarioSelection();

	while (scenarioSelection == scenarios.size() + 1)
	{
		message.clear();
		message.append("=> Test : ");
		message.append(selectedTest);
		message.append("\n** Vlastny scenar **");
		addNewADTScenatio();
		printScenarioSelection();
	}

	system("cls");
	message.clear();
	message.append("=> Test : ");
	message.append(selectedTest);
	message.append("\n=> Scenar : ");
	message.push_back(scenarios[scenarioSelection - 1]);

	/********** Confirm run test **********/
	printConfirmation();
	

	cout << message << endl;
	cout << "\n***********************\n";

	test->runTest(scenarios[scenarioSelection - 1], *info);

	cout << "***********************\n";
	cout << "Test bol vykonany...\n";

	/********** Test results **********/
	printTestResults();
}

bool TestApp::initializeTest(int testSelection)
{
	switch (testSelection)
	{
	case 1:
		test = new ADTListTest();
		selectedTest = "ADT List";
		break;
	case 2:
		test = new ADTPriortityQueueTest();
		selectedTest = "ADT Priority Queue";
		break;
	case 3:
		test = new MatrixTest();
		selectedTest = "Matrix";
		break;
	default:
		return false;
	}

	return true;
}

bool TestApp::addNewADTScenatio()
{
	int insert = 0, remove = 0, get = 0, index = 0;
	char sName = ' ';
	string rawInput;
	system("cls");

	cout << message << endl;
	message.clear();
	message.append("=> Test : ");
	message.append(selectedTest);

	cout << "\nNazov(znak): ";
	cin >> rawInput;
	if (cin.fail()) {
		cin.clear();
		cin.ignore();
		rawInput.clear();
		rawInput = "";
	}
	while (rawInput == "" || rawInput.size() > 1)
	{
		onceAgainSelection(sName, rawInput);
	}

	sName = rawInput[0];

	cout << "Insert podiel: ";
	cin >> insert;
	if (cin.fail()) {
		cin.clear();
		cin.ignore();
		insert = -1;
	}
	while (insert == -1)
	{
		onceAgainSelection(insert);
	}

	cout << "Remove podiel: ";
	cin >> remove;
	if (cin.fail()) {
		cin.clear();
		cin.ignore();
		remove = -1;
	}
	while (remove == -1)
	{
		onceAgainSelection(remove);
	}

	cout << "Get podiel: ";
	cin >> get;
	if (cin.fail()) {
		cin.clear();
		cin.ignore();
		get = -1;
	}
	while (get == -1)
	{
		onceAgainSelection(get);
	}

	cout << "Index podiel: ";
	cin >> index;
	if (cin.fail()) {
		cin.clear();
		cin.ignore();
		index = -1;
	}
	while (index == -1)
	{
		onceAgainSelection(index);
	}

	system("cls");

	FileOutputHander foh;
	string nLine;
	ostringstream s;

	foh.openFile("test.csv", "app");
	s << sName << ';' << insert << ';' << remove << ';' << get << ';' << index;
	nLine = s.str();

	if (insert + remove + get + index != 100 || sName == ' ' || !foh.writeLine(nLine))
	{
		message.append("\n!Scenar sa nepodarilo ulozit!");
		return false;
	} 
	else
	{
		message.append("\n*Scenar uspesne pridany*");
	}
	return true;
}

void TestApp::onceAgainSelection(int& varToSelect)
{
	cout << "\nSkuste to este raz: ";
	cin >> varToSelect;
	if (cin.fail()) {
		cin.clear();
		cin.ignore();
		varToSelect = -1;
	}
}

void TestApp::onceAgainSelection(char& varToSelect, std::string& rawInput)
{
	cout << "\nSkuste to este raz: ";
	cin >> rawInput;
	if (cin.fail()) {
		cin.clear();
		cin.ignore();
		rawInput.clear();
		rawInput = "";
	}
}


void TestApp::printStructTestSelection()
{
	cout << "Vyberte test, ktory sa ma spusit:\n";
	cout << "\t1 - ADT List\n";
	cout << "\t2 - ADT Priority Queue\n";
	cout << "\t3 - Matrix (implementing in progress)\n";
	cout << "Vas vyber: ";
	cin >> testSelection;
	if (cin.fail())
	{
		cin.clear();
		cin.ignore();
		testSelection = -1;
	}
	while (!initializeTest(testSelection))
	{
		onceAgainSelection(testSelection);
	}
}

void TestApp::printScenarioSelection()
{
	cout << message << endl;
	cout << "\nVyberte testovaci scenar: \n";

	scenarios.clear();
	scenarios = test->getScenarios();
	int i = 0;
	while (scenarios[i] != '\0')
	{
		cout << "\t" << i << " - " << scenarios[i++] << endl;
	}
	//Pri ADT Liste je mozne si navolit vlastny test
	if (selectedTest == "ADT List")
	{
		cout << "\t" << i + 1 << " - " << "Vytvorit novy scenar" << endl;
	}

	cout << "Vas vyber: ";
	cin >> scenarioSelection;
	if (cin.fail())
	{
		cin.clear();
		cin.ignore();
		scenarioSelection = -1;
	}
	while (scenarioSelection < 1 || scenarioSelection > scenarios.size())
	{
		//Volba pre vlastny test
		if (selectedTest == "ADT List" && scenarioSelection == scenarios.size() + 1)
		{
			system("cls");
			break;
		}
		onceAgainSelection(scenarioSelection);
	}
}

void TestApp::printConfirmation()
{
	cout << message << endl;
	cout << "\nPrajete si spustit zvoleny test a scenar?\n";
	cout << "\t1 - ano\n";
	cout << "\t2 - nie\n";
	cout << "Vas vyber: ";
	cin >> confirmSelection;
	while (confirmSelection != 1 && confirmSelection != 2)
	{
		onceAgainSelection(confirmSelection);
	}

	system("cls");

	/*!! Stops applicaton !!*/
	if (confirmSelection == 2)
	{
		return;
	}
}

void TestApp::printTestResults()
{
	cout << "\nVysledok: \n";
	cout << info->getMessage();
	cout << "=> Celk. cas operacii : " << info->getOperationsTime() << "s\n";	
}
