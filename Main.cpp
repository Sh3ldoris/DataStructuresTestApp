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
#include "structures/list/CyclicLinkedList.h"
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
	/*CyclicedLikedList<int> cl;
	cl.add(1);
	cl.add(2);
	cl.add(3);
	cl.insert(4, 2);

	for (int data : cl)
	{
		cout << data << " - ";
	}
	cout << endl;*/
	return 0;
}

