#include <iostream>
#include "structures/list/list.h"
#include "structures/list/array_list.h"
#include "structures/list/linked_list.h"
#include "ADTListTest.h"
#include "FileOutputHander.h"
#include "TestApp.h"

using namespace structures;
using namespace std;

int main()
{
	initHeapMonitor();
	TestApp app;
	app.run();
	return 0;
}

