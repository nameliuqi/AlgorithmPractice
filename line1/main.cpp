#include <iostream>
#include <limits.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

int randomint()
{
    srand((int)time(0));
    srand((int)time(0));
    const int n = 50;
    int i;
    i=0;
    while (n > (rand()%100))
    {
        i++;
    }
    return i;
}

//supposing all the value of Node is positive
class Node
{
    public:
        int getValue()
        {
            return value;
        }
        int setValue(int n)
        {
            int temp;
            temp = value;
            value = n;
            return temp;
        }
        Node()
        {
            value = 0;
            *down = NULL;
            *left = NULL;
            *right = NULL;
        }
        Node(int n)
        {
            value = n;
            *down = NULL;
            *left = NULL;
            *right = NULL;
        }
        Node *down,*left,*right;
        int value;
};

class Skiplist
{
    public:
        Node *head,*tail;
        int insert(int num);
        int del(int num);
        Node* find(int num);
        int getSize();
        int getHeight();
        Skiplist();
    private:
        int n,h;
};

Skiplist::Skiplist()
{
    n=0;
    h=0;
    head = NULL;
    tail = NULL;
}

Node* Skiplist::find(int num)
{
    Node *p;
    p = head;
    while (1)
    {
        if (!p->down)
            break;
        else
        {
            while (p->value<=num)
                p=p->right;
            if (p->down)
                p = p->down;
        }
    }
    return p;
}

int Skiplist::getHeight()
{
    return h;
}

int Skiplist::getSize()
{
    return n;
}

int Skiplist::del(int num)
{
    Node *found;
    found = find(num);
    if ((*found).value!=num)
        return -1;
    Node *p;
    p = head;
    while (p->down)
    {
        while (p->value<=num)
        p = p->right;
        if (p->value ==num)
        {
            (p->right)->left = p->left;
            (p->left)->right = p->right;
            delete p;
        }
        else
            p=p->down;
    }
    return p->getValue();
}

int Skiplist::insert(int num)
{
    //already had
    if ((find(num))->value == num)
        return -1;
    int i;
    i = randomint();

    while (i>h)
    {
        Node *thead = new Node();
        Node *ttail = new Node();
        thead->down = head;
        ttail->down = tail;
        thead->right = ttail;
        ttail->left = thead;
        head = thead;
        tail = ttail;
        h++;
    }

    Node *p,*now;
    p = head;

    //find the level
    while (i<h)
    {
        p = p->down;
        i++;
    }
    //find the position in level i
    while (p->value<num)
    {
        p = p->right;
    }
    //the first insert
    now  = new Node(num);
    now->right = p->right;
    (now->right)->left = now;
    now->left = p;
    p->right = now;
    //insert the rest
    while (p->down)
    {
        Node * temp;
        p = p->down;
        while (p->value<num)
        {
            p = p->right;
        }
        temp = new Node(num);
        now->down = temp;
        temp->right [p0]= p->right;
        temp->left = p;
        (temp->right)->left = temp;
        p->right = temp;
        now = temp;
    }
    return num;
}

int main()
{
    cout<<"hello world";
    return 0;
}

