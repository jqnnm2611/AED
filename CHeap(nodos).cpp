#include <iostream>
#include <assert.h>
using namespace std;

struct mayor
{
    bool operator()(int a, int b) {
        return a > b;
    }
};

struct menor
{
    bool operator()(int a, int b) {
        return a < b;
    }
};

struct CNode
{
    CNode(int v)
    {
        value = v;
        left = right = parent = 0;
    }

    int value;
    CNode *left, *right, *parent;
};

template <class O>
class CHeap
{
    public:
        CHeap();
        ~CHeap();
        void push(int x);
        void pop();
        void rem(int x);
        int& top();
        bool empty();
        int size();
        void print();
    private:
        CNode *root, *next;
        int elem;
};

template <class O>
CHeap<O>::CHeap()
{
    root = next = 0;
    elem = 0;
}

template <class O>
CHeap<O>::~CHeap()
{
}

template <class O>
void CHeap<O>::push(int x)
{
    if(elem == 0)
    {
        root = new CNode(x);
        next = root;
    }
    else
    {
        if(next->left == 0)
        {
            next->left = new CNode(x);
            next->left->parent = next;
        }
        else 
        {
            next->right = new CNode(x);
            next->right->parent = next;
        }
        
    }
    elem++;
}

template <class O>
void CHeap<O>::pop()
{
}

template <class O>
void CHeap<O>::rem(int x)
{
}

template <class O>
int& CHeap<O>::top()
{
}

template <class O>
bool CHeap<O>::empty()
{
}

template <class O>
int CHeap<O>::size()
{
}

template <class O>
void CHeap<O>::print()
{
}



int main()
{
    
    
    
    return 0;
}
