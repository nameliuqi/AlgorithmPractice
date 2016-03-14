#include "stdio.h"
#include "stdlib.h"
#include "iostream"
#define MAX 100
using namespace std;

class priority
{
public:
    int enqueue(int num);
    int dequeue();
    int top();
    int getSize();
    int empty();
    int print();
    priority()
    {
        size = 0;
    }
private:
    int heap[MAX];
    int size;
};

int priority::enqueue(int num)
{
    size++;
    heap[size] = num;
    int par,chid;
    chid = size;
    par = chid/2;
    while ((par > 0) && (heap[par] > heap[chid]))
    {
        swap(heap[par],heap[chid]);
        chid = par;
        par = chid/2;
    }
}

int priority::dequeue()
{
    int num;
    if (empty())
    {
        cout<<"empty while dequeue\n";
        //supposing all the value is positive
        return -1;
    }
    num = heap[size--];
    heap[1] = heap[size+1];
    int par;
    par = 1;
    while (par <= size/2)
    {
        int chid1,chid2;
        chid2 = par*2+1;
        chid1 = par*2;
        if (heap[par] < heap[chid1]) && (heap[par] < heap[chi2])
    }
}

int priority::top()
{

}

int priority::getSize()
{

}

int priority::empty()
{

}

int priority::print()
{

}

int main(int argc, char const *argv[])
{
    return 0;
}
