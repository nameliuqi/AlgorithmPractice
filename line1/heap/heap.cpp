#include "stdio.h"
#include "stdlib.h"
#include "iostream"
#define MAX 100
using namespace std;

void swap(int &a,int &b)
{
    int temp;
    temp = a;
    a = b;
    b = temp;
}

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
    num = heap[1];
    heap[1] = heap[size];
    size--;
    int par;
    par = 1;
    while (par <= size/2)
    {
        int chid;
        chid = par*2;
        if (chid == size)
            if (heap[chid]<heap[par])
                swap(heap[chid],heap[par]);
            else
                ;
        else
        {
            chid = heap[chid] < heap[chid+1] ? chid:(chid+1);
            swap(heap[chid],heap[par]);
        }
        par = chid;
    }
    return num;
}

int priority::top()
{
	return heap[1];
}

int priority::getSize()
{
	return size;
}

int priority::empty()
{
	return size==0;
}

int priority::print()
{
	for (int i = 0; i < size; ++i)
	{
		cout<<heap[i+1]<<endl;
	}
}

int main(int argc, char const *argv[])
{
	int n;
	priority *p = new priority();
	cout<<"input the number n"<<endl;
	cin>>n;
	while (n--)
	{
		int temp;
		cin>>temp;
		p->enqueue(temp);
	}
	cout<<"print the heap:\n";
	p->print();
	cout<<"input the number n again"<<endl;
	cin>>n;
	while ((n--) && (!p->empty()))
	{
		cout<<"out: "<<p->dequeue()<<endl;
	}
	cout<<"print the heap again:\n";
	if (!p->empty())
		p->print();
    return 0;
}
