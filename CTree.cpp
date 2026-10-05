#include <iostream>
#include <stack>
#include <utility>
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
    bool find(int x, CNode**& p);
    bool ins(int x);
    bool rem(int x);
    CNode** rep(CNode**p);
    void inorder(CNode* n);
    void reverse(CNode* n);
    void preorder(CNode* n);
    void postorder(CNode* n);
    void inorder_s(CNode* n);
    void print();
private:
    CNode* root;
    bool brep;
};

CTree::CTree()
{
    root = 0;
    brep = 0;
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
    CNode** p;
    if ( !find(x,p) ) return 0;
    
    if ( (*p)->left && (*p)->right )
    {
        CNode** q = rep(p);
        (*p)->value = (*q)->value;
        p = q;
    }
    CNode* t = *p;
    if ( (*p)->right )
        *p = (*p)->right;
    else
        *p = (*p)->left;
    delete t;
    return 1;
}
CNode** CTree::rep(CNode**p)
{
    CNode** q = p;
    if ( brep == 1 )
    {
        q = &((*q)->right);
        while ( (*q)->left )
            q = &((*q)->left);
    }
    else
    {
        q = &((*q)->left);
        while ( (*q)->right )
            q = &((*q)->right);
    }
    brep = !brep;
    return q;
}
void CTree::inorder(CNode* n)
{
    if(!n) return;
    inorder(n->left);
    cout << n->value << ' ';
    inorder(n->right);
}
void CTree::reverse(CNode* n)
{
    if(!n) return;
    reverse(n->right);
    cout << n->value << ' ';
    reverse(n->left);
}
void CTree::preorder(CNode* n)
{
    if(!n) return;
    cout << n->value << ' ';
    preorder(n->left);
    preorder(n->right);
}
void CTree::postorder(CNode* n)
{
    if(!n) return;
    postorder(n->left);
    postorder(n->right);
    cout << n->value << ' ';
}
/*void CTree::inorder_s(CNode* n)
{
    stack<pair<CNode*,int>> s;
    s.push({n,0});
    while(!s.empty())
    {
        auto e = s.top();
        switch(e.second)
        {
            case 0:
                //completar
        }
    }
}*/



void CTree::print()
{
    inorder(root);
    cout << endl;
}

int main()
{
    CTree t;

    t.ins(52);
    t.ins(43);
    t.ins(73);
    t.ins(31);
    t.ins(47);
    t.ins(61);
    t.ins(84);
    
    t.print();
    
    return 0;
}
