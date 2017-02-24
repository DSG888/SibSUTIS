#ifndef LINKLIST_H
#define	LINKLIST_H

class LinkedList
{
	public:
		LinkedList();
		LinkedList(const LinkedList& orig);
		~LinkedList();
		
		void appendNode(const int d);
		bool insertNode(const int d, const int i);
		bool deleteNode(const int i);
		void emptyList();
		
		void print();
		void printReverse();
		void printOne(const int i);
		
		int getSize() const { return size; }
		
		LinkedList operator=(const LinkedList &orig);
		int operator[](int i);
	private:
		int size;
		struct Node{
			int data;
			Node *prev;
			Node *next;
		} *head;
};

#endif
