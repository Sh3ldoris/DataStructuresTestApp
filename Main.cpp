#include <iostream>
#include <sstream>
#include <fstream>
#include <cctype>
#include <string>
#include "structures/list/list.h"
#include "structures/list/array_list.h"
#include "structures/list/linked_list.h"
#include "structures/matrix/Matrix.h"
#include "structures/matrix/CoherentMatrix.h"
#include "structures/matrix/IncoherentMatrix.h"
#include "ADTListTest.h"
#include "FileOutputHander.h"
#include "TestApp.h"

using namespace structures;
using namespace mystruct;
using namespace std;

int main()
{
	initHeapMonitor();
	TestApp app;
	app.run();

	/*ADTListTest a;
	string s = a.getScenarios();*/

	/*Matrix<int>* m = new IncoherentMatrix<int>(5, 6);
	m->setValues(0);
	m->item(2, 3) = 8;
	for (int i = 0; i < m->getColumnLength(); i++)
	{
		for (int j = 0; j < m->getRowLength(); j++)
		{
			cout << m->item(i, j);
		}
		cout << endl;
	}
	delete m;*/

	
	return 0;
}

