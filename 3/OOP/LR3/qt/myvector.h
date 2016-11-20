#ifndef MYVECTOR_H
#define MYVECTOR_H

#include <iostream>
#include <exception>
#include <stdexcept>
#include <new> //needed for BAD_ALLOC
using namespace std;

template <class T>
class myVector{
    private:
        T* arr;
        unsigned int Size; //keeps track of own size
        int capacity;
        //private member function
        //example of OOP encapsulation
        void grow()
        {
            capacity *= 2;
            try
            {
                T* temp = new T[capacity];
                for(int i = 0;i < Size;i++)
                {
                    temp[i] = arr[i];	   //fill new larger array with old values
                }
                delete [] arr; //deletes what's at old location
                arr = temp;  //now array points to new larger location in memory
            }
            catch(bad_alloc)
            {
                cout << "ERROR: BAD_ALLOC...FAILED TO ALLOCATE MEMORY" << endl;
//				exit(1);
            }
        }
    public:
        unsigned int size() const //returns current size of vector
        {
            return Size;
        }
        int getCapacity() const
        {
            return capacity;
        }
        void push_back(const T& elt) //insert element elt at end of vector
        {
            if(Size == capacity)//current array is full
                grow();
            arr[Size] = elt; //size points one position past end
            Size++; //keep track of array size
        }

        void pop_back()   //delete last element
        {
            if(Size >= 1)	//if array is not empty
            {
                Size--;
                delete arr[Size];
            }
            else
                cout << "ERROR: UNDERFLOW" << endl;

            //}catch(std::underflow_error){	  //just throw type
            //	 cout << "ERROR: UNDERFLOW_ERROR...VECTOR IS EMPTY" << endl << "CANNOT REMOVE ELEMENT" << endl;
                //	exit(1);
            //  }
        }
        T& at(int pos)  //returns reference to element at position pos if pos is valid
        {
            if(pos < Size && pos >= 0){
                    return arr[pos];
            }
            else
                    throw exception();
        }

        T& front()
        {
            if(Size >= 1)
                return arr[0];
            else
                cout << "ERROR: VECTOR EMPTY" << endl;
        }
        T& back()
        {
            if(Size >= 1)
            {
                return arr[Size - 1];
            }
            else
                cout << "ERROR: VECTOR EMPTY" << endl;
//						 exit(1);
        }
        bool empty()
        {   //returns true if vector is empty
            if(Size < 1)
                return true;
            return false;
        }

        void insert(const T& elt, int pos)  //insert element elt at position pos
        {
            if(Size > 0 && pos < Size)
            {
                if(Size == capacity)
                    grow();
                for(int i = Size; i > pos; i--)
                {
                    arr[i] = arr[i - 1];
                }
                arr[pos] = elt;
                Size++;
            }
            else
                throw exception();
        }

        void erase(int pos)   //deletes element at position pos
        {
            if(Size > 0 && pos < Size)
            {
                Size--; //keep track of reduced size
                for(int i = pos; i < Size; i++)
                {
                    arr[i] = arr[i + 1];
                }
            }
            else
                throw exception();
        }

        //overloaded operators
        T& operator[](int n)   //returns reference to element at position n
        {
            return arr[n];
        }

        //overloaded operator= required to prevent memberwise assignment
        //returns value of left operand to allow multiple assignment stmts, i.e. a = b = c
        myVector<T>& operator=(myVector<T>& v)
        {
            if(Size > 0)
            {		 //if vector not empty, clear first
                delete [] arr;
            }
            Size = v.size();	 //implicit this parameter
            capacity = v.getCapacity();
            arr = new T[capacity];
            for(int i = 0; i < Size; i++)
                arr[i] = v.at(i);
            return *this;
        }

        //default constructor
        myVector()
        {
            Size = 0;
            capacity = 10;
            try
            {
                arr = new T[capacity];
            }
            catch(bad_alloc)
            {
                cout << "ERROR: BAD_ALLOC...FAILED TO ALLOCATE MEMORY" << endl;
//				exit(1);
            }
        }

        //copy constructor
        //prevents memberwise assignment i.e. two objects pointing to same address
        //usage: v1(v2);
        myVector(const myVector<T>& v)
        {
            Size = v.size();  //must use mutator function for private members
            capacity = v.getCapacity();
            try
            {
                    arr = new T[capacity];
            }
            catch(bad_alloc)
            {
                    cout << "ERROR: BAD_ALLOC...FAILED TO ALLOCATE MEMORY" << endl;
            }
            for(int i = 0; i < Size; i++)
            {
                    arr[i] = v.at(i);   //at method checks bounds
            }
        }

        //destructor
        ~myVector()
        {
            if (Size > 0)
            {
                delete [] arr;
            }
        }
};

#endif // MYVECTOR_H
