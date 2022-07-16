//
// Created by bong on 22. 7. 15.
//

#include <iostream>
#include "../../framework/utils/CustomQueue.h"
using namespace std;

int main(){
    cout << "util example" << endl;

    MpscLockQueue<int> test;
    cout << "queue is empty? " << test.empty() << endl;

    test.enqueue(5);
    test.enqueue(10);

    cout << "queue is empty? " << test.empty() << endl;

    int a;
    cout << test.dequeue(a) << " queue value " << a << endl;

    cout << test.dequeue(a) <<  " queue value " << a << endl;

    cout << test.dequeue(a) <<  " queue value " << a << endl;

    //cout << "queue is empty? " << test.empty() << endl;







/*    while(test.empty()){

    }*/



    return 0;
}