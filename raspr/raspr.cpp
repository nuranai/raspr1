// raspr.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>
#include <random>

using namespace std;

int main()
{
    srand(time(NULL));
    minstd_rand rnad_num(rand());
    int arrNum, threadNum;
    arrNum = 31;
    threadNum = 4;
    
    int* arr = new int[arrNum];
    int* check = new int[arrNum];
    thread* threadArr = new thread[threadNum];

    for (int i = 0; i < arrNum; i++) {
        check[i] = 0;
    }

    int spanSize = ceil(double(arrNum) / threadNum);
    int threadStart = 0;
    int threadCounter = 0;
    while (threadStart != arrNum) {
        
        int increment = std::min(arrNum - threadStart, spanSize);
        int threadMax = threadStart + increment;
        threadArr[threadCounter] = thread ([start = threadStart, end = threadMax, &arr, &check, rnad_num]() mutable {
            while (start < end) {
                
                arr[start] = rnad_num() % 100;
                check[start]++;

                start++;
            }
        });
        rnad_num.discard(increment);
        threadStart += increment;
        threadCounter++;
    }
    for (int i = 0; i < threadNum; i++) {
        threadArr[i].join();
    }

    for (int i = 0; i < arrNum; i++) {
        cout << arr[i] << ' ';
    }
    cout << endl << "was setted once::";
    bool res = true;
    for (int i = 0; i < arrNum; i++) {
        res = res && check[i] == 1;
    }
    cout << (res ? "true" : "false");
}