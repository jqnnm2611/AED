#include <iostream>
#include <assert.h>
using namespace std;

struct CNode
{
    CNode(int v)
    {
        value = v;
        next = prev = 0;
    }
    int value;
    CNode *next, *prev;
};

class CList
{
public:
    CList();
    ~CList();
    void push_front(int x);
    void pop_front();
    void push_back(int x);
    void pop_back();
    int& operator[](int i);
    int& front();
    int& back();
    void print();

private:
    CNode *head, *tail;
    int elem;
};

CList::CList()
{
    head = tail = 0;
    elem = 0;
}
CList::~CList()
{
    while(head) pop_front();
}
void CList::push_front(int x)
{
    CNode* t = new CNode(x);
    if(elem == 0) head = tail = t;
    else
    {
        t->next = head;
        head->prev = t;
        head = t;
    }
    elem++;
}
void CList::pop_front()
{
    assert(elem > 0);
    CNode* t = head;
    if (elem == 1) head = tail = 0;
    else
    {
        head = t->next;
        head->prev = 0;
    }
    delete t;
    elem--;
    
}
void CList::push_back(int x)
{
    CNode* t = new CNode(x);
    if(elem == 0) tail = head = t;
    else
    {
        t->prev = tail;
        tail->next = t;
        tail = t;
    }
    elem++;
}
void CList::pop_back()
{
    assert(elem > 0);
    CNode* t = tail;
    if (elem == 1) tail = head = 0;
    else
    {
        tail = t->prev;
        tail->next = 0;
    }
    delete t;
    elem--;
}
int& CList::operator[](int i)
{
    assert(i >= 0 && i < elem);;
    CNode* q = head;
    for(int k = 0; k < i; k++, q = q->next);
    return q->value;
}
int& CList::front()
{
    assert(elem > 0);
    return head->value;
}
int& CList::back()
{
    assert(elem > 0);
    return tail->value;
}
void CList::print()
{
    for(CNode* q = head; q; q = q->next) cout << q->value << ' ';
    cout << endl;
}


int main()
{
    CList v;
    v.push_back(3);
    v.push_back(7);
    v.push_back(6);
    v.push_front(1);
    v.push_front(9);
    v.push_front(2);
    v.print();
        
    v[3] = 4;
    v.print();
    
    v.front() = 1;
    v.back() = 1;
    v.print();

    
    v.pop_back();
    v.pop_front();
    v.print();

    v.pop_back();
    v.pop_front();
    v.print();

    v.pop_back();
    v.pop_front();
    v.print();
    
    cout<<endl;
}
