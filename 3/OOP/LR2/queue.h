#define SIZE 10     //size of array
#include <stdio.h>

class queue{
public:
    int array[SIZE];
    int f,r;    //indicates front & rear end of queue
    queue(){    //constructor to initialize f & r values
        f=0;
        r=-1;
    }
    void ins(int x){    // function to insert data
        r++;
        array[r]=x;     //element added to queue’s rear end
    }
    int del(){  // function to delete data from queue
        int x;
        x=array[f];
        f++;    //element removed from queue’s front
        return x;
    }
    int peek(){     // function to peek data from queue
        int x;
        x=array[f];     //element from queue’s front
        return x;
    }
    void show_queue(){   // function to see data in queue
        int i;
        printf("\n");
        for(i=f;i<=r;i++){
            printf("<%d ", array[i]);
        }
        printf("\n");
    }
    int isqueueempty(){     // function to check if queue is empty
        if(f==(r+1))
            return 1;
        else
            return 0;
    }
    int isqueuefull(){      // function to check if queue is full
        if(r==SIZE-1)
            return 1;
        else
            return 0;
    }
};
