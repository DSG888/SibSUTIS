#include "queue.h"

Queue::Queue()
{
}

void Queue::enqueue(const int d)
{
	appendNode(d);
}

void Queue::dequeue()
{
	printOne(0);
	deleteNode(0);
}
