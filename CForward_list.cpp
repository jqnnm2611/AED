#include <iostream>
#include <assert.h>
using namespace std;

struct CNode
{
    CNode(int v)
    {
        value = v;
        next = 0;
    }
    
    int value;
    CNode* next;
};

class CForward_list
{
public:
    CForward_list();
    ~CForward_list();
    void push_front(int x);
    void pop_front();
    void push_back(int x);
    void pop_back();
    int& operator[](int i);
    int& front();
    int& back();
    void print();

private:
    CNode* head;
    int elem;
};

CForward_list::CForward_list()
{
    head = 0;
    elem = 0;
}
CForward_list::~CForward_list()
{
    while(head)
    {
        CNode* t = head;
        head = head->next;
        delete t;
    }
}
void CForward_list::push_front(int x)
{
    CNode* t = new CNode(x);
    t->next = head;
    head = t;
    elem++;
}
void CForward_list::pop_front()
{
    assert(elem > 0);
    CNode* t = head;
    head = t->next;
    delete t;
    elem--;
}
void CForward_list::push_back(int x)
{
    CNode** p;
    for(p = &head; *p != 0; p = &((*p)->next));
    *p = new CNode(x);
    elem++;
}
void CForward_list::pop_back()
{
    assert(elem > 0);
    CNode** p;
    for(p = &head; (*p)->next != 0; p = &((*p)->next));
    delete *p;
    *p = 0;
    elem--;
}
int& CForward_list::operator[](int i)
{
    assert(i >= 0 && i < elem);
    CNode* q = head;
    for(int k = 0; k < i; k++, q = q->next);
    return q->value;
}
int& CForward_list::front()
{
    assert(elem > 0);
    return head->value;
}
int& CForward_list::back()
{
    CNode* q = head;
    for(int k = 0; k < elem - 1; k++, q = q->next);
    return q->value;
}
void CForward_list::print()
{
    for(CNode* p = head; p; p = p->next) cout << p->value << ' ';
    cout << endl;
}


int main()
{
    CForward_list v;
    v.push_back(3);
    v.push_back(7);
    v.push_back(6);
    v.push_front(1);
    v.push_front(9);
    v.push_front(2);
    v.print();
    v.pop_back();
    v.pop_front();
    v.print();
    
    v[3] = 4;
    v.print();
    
    v.front() = 1;
    v.back() = 1;
    v.print();
    
    cout<<endl;
}
