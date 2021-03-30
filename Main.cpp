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
#include "structures/priority_queue/priority_queue.h"
#include "structures/priority_queue/priority_queue_sorted_array_list.h"
#include "structures/priority_queue/priority_queue_unsorted_array_list.h"
#include "structures/priority_queue/heap.h"
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
	return 0;
}

