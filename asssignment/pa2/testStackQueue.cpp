#define CATCH_CONFIG_MAIN
#include <iostream>

#include "cs221util/catch.hpp"
#include "queue.h"
#include "stack.h"

using namespace std;

TEST_CASE("stack::basic functions", "[weight=1][part=stack]")
{
    // cout << "Testing Stack..." << endl;
    Stack<int> intStack;
    vector<int> result;
    vector<int> expected;
    for (int i = 10000; i > 0; i--)
    {
        expected.push_back(i);
    }
    for (int i = 1; i <= 10000; i++)
    {
        intStack.push(i);
    }
    // cout << intStack.peek() << endl;
    while (!intStack.isEmpty())
    {
        result.push_back(intStack.pop());
        // cout << intStack.pop() << " ";
    }
    REQUIRE(result == expected);
}

TEST_CASE("queue::basic functions", "[weight=1][part=queue]")
{
    // cout << "Testing Queue..." << endl;
    Queue<int> intQueue;
    vector<int> result;
    vector<int> expected;
    for (int i = 1; i <= 100000; i++)
    {
        expected.push_back(i);
    }
   // cout << "=========enqueu======" << endl;
    for (int i = 1; i <= 100000; i++)
    {
        //cout << i << endl;
        intQueue.enqueue(i);
    }
    // cout << "=========dequeue======" << endl;
    while (!intQueue.isEmpty())
    {
        int x = intQueue.dequeue();
        result.push_back(x);
         //cout << x << endl;
    }
    REQUIRE(result == expected);
}
