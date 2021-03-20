#include "TestApp.h"
#include "ADTListTest.h"
#include "structures/list/list.h"
#include "structures/list/array_list.h"
#include <iostream>

using namespace structures;
using namespace std;

TestApp::TestApp():
	info(new TestInfo()),
	test(nullptr)
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
	int testSelection, scenarioSelection, confirmSelection = -1;

	/********** Test type selection **********/
	cout << "Vyberte test, ktory sa ma spusit:\n";
	cout << "\t1 - ADT List\n";
	cout << "\t2 - Not yet\n";
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

	system("cls");
	cout << "=> Test : " << selectedTest << endl;


	/********** Test scenario selection **********/
	cout << "\nVyberte testovaci scenar: \n";

	const char* scenarios = test->getScenarios();
	int i = 0;
	while (scenarios[i] != '\0')
	{
		cout << "\t" << i << " - " << scenarios[i++] << endl;
	}
	cout << "Vas vyber: ";
	cin >> scenarioSelection;
	if (cin.fail())
	{
		cin.clear();
		cin.ignore();
		scenarioSelection = -1;
	}
	while (scenarioSelection < 1 || scenarioSelection > i)
	{
		onceAgainSelection(scenarioSelection);
	}

	system("cls");
	cout << "=> Test : " << selectedTest << endl;
	cout << "=> Scenar : " << scenarios[scenarioSelection - 1] << endl;

	/********** Confirm run test **********/
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

	cout << "=> Test : " << selectedTest << endl;
	cout << "=> Scenar : " << scenarios[scenarioSelection - 1] << endl;
	cout << "\n***********************\n";
	cout << "Test prave prebieha...\n";

	test->runTest(scenarios[scenarioSelection - 1], *info);

	cout << "***********************\n";
	cout << "Test bol vykonany...\n";
	cout << "***********************\n";


	cout << "\n=> Pocet vykonanych operacii : " << info->getOperationsCount() << endl;
	cout << "=> Celk. cas operacii : " << info->getOperationsTime() << endl;
	cout << "\n\n";
}

bool TestApp::initializeTest(int testSelection)
{
	switch (testSelection)
	{
	case 1:
		test = new ADTListTest();
		selectedTest = "ADT List";
		break;
	default:
		return false;
	}

	return true;
}

void TestApp::onceAgainSelection(int& varToSelect)
{
	cout << "Skuste to este raz: ";
	cin >> varToSelect;
	if (cin.fail()) {
		cin.clear();
		cin.ignore();
		varToSelect = -1;
	}
}
