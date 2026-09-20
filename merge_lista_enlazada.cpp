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
    CNode*& getHead();

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
CNode*& CForward_list::getHead()
{
    return head;
}


class merge
{
public:
    void ejecuta(CNode*& l1, CNode*& l2);
    void print(CNode* l);
};

void merge::ejecuta(CNode*& l1, CNode*& l2)
{
    if(l1 == 0)
    {
        l1 = l2;
        l2 = 0;
        return;
    }

    if(l2 == 0) return;

    CNode* inicio;
    if(l1->value < l2->value)
    {
        inicio = l1;
        l1 = l1->next;
    }
    else
    {
        inicio = l2;
        l2 = l2->next;
    }

    CNode* p = inicio;
    while(l1 != 0 && l2 != 0)
    {
        if(l1->value < l2->value)
        {
            p->next = l1;
            l1 = l1->next;
        }
        else
        {
            p->next = l2;
            l2 = l2->next;
        }
        p = p->next;
    }
    if(l1 != 0)
        p->next = l1;
    else
        p->next = l2;
    l1 = inicio;
    l2 = 0;
}
void merge::print(CNode* l)
{
    for(; l; l = l->next) cout << l->value << ' ';
    cout << endl;
}


int main()
{
    CForward_list l1;
    CForward_list l2;

    l1.push_back(1);
    l1.push_back(3);
    l1.push_back(8);
    l1.push_back(9);
    l1.push_back(10);

    l2.push_back(4);
    l2.push_back(5);
    l2.push_back(11);

    merge m;
    m.ejecuta(l1.getHead(), l2.getHead());
    m.print(l1.getHead());
}
