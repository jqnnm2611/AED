#include <iostream>
#include <assert.h>
using namespace std;

struct CNode
{
    CNode(int v)
    {
        value = v;
        left = right = 0;
    }
    int value;
    CNode *left, *right;
};

class CTree
{
public:
    CTree();
    ~CTree();
    bool find(int x, CNode** p);
    bool ins(int x);
    bool rem(int x);
private:
    CNode* root;
};

CTree::CTree()
{
    root = 0;
}
CTree::~CTree()
{
    
}
bool CTree::find(int x, CNode**& p)
{
    p = &root;
    while(*p && (*p)->value != x)
    {
        if((*p)->value < x) p = &((*p)->right);
        else p = &((*p)->left);
    }
    return *p != 0;
}
bool CTree::ins(int x)
{
    CNode** p;
    if(find(x,p)) return 0;
    *p = new CNode(x);
    return 1;
}
bool CTree::rem(int x)
{
    
}

int main()
{
    return 0;
}
