#include <iostream>
#include <stack>
#include <utility>
#include <queue>
#include <algorithm>
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
    void reverse_s(CNode* n);
    void preorder_s(CNode* n);
    void postorder_s(CNode* n);
    void levelorder(CNode* n);
    int maxh(CNode* n);
    void maxh2(CNode* n, int h, int& mh);
    void print();
    void print_h();
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
void CTree::inorder_s(CNode* n)
{
    if(!n) return;
    stack<pair<CNode*,int>> s;
    s.push({n,0});
    while(!s.empty())
    {
        auto& e = s.top();
        switch(e.second)
        {
            case 0:
                e.second = 1;
                if(e.first->left) s.push({e.first->left,0});
                break;
            case 1:
                e.second = 2;
                cout << e.first->value << ' ';
                break;
            case 2:
                e.second = 3;
                if(e.first->right) s.push({e.first->right,0});
                break;
            case 3:
                s.pop();
                break;
        }
    }
}
void CTree::reverse_s(CNode* n)
{
    if(!n) return;
    stack<pair<CNode*,int>> s;
    s.push({n,0});
    while(!s.empty())
    {
        auto& e = s.top();
        switch(e.second)
        {
            case 0:
                e.second = 1;
                if(e.first->right) s.push({e.first->right,0});
                break;
            case 1:
                e.second = 2;
                cout << e.first->value << ' ';
                break;
            case 2:
                e.second = 3;
                if(e.first->left) s.push({e.first->left,0});
                break;
            case 3:
                s.pop();
                break;
        }
    }
}
void CTree::preorder_s(CNode* n)
{
    if(!n) return;
    stack<pair<CNode*,int>> s;
    s.push({n,0});
    while(!s.empty())
    {
        auto& e = s.top();
        switch(e.second)
        {
            case 0:
                e.second = 1;
                cout << e.first->value << ' ';
                break;
            case 1:
                e.second = 2;
                if(e.first->left) s.push({e.first->left,0});
                break;
            case 2:
                e.second = 3;
                if(e.first->right) s.push({e.first->right,0});
                break;
            case 3:
                s.pop();
                break;
        }
    }
}
void CTree::postorder_s(CNode* n)
{
    if(!n) return;
    stack<pair<CNode*,int>> s;
    s.push({n,0});
    while(!s.empty())
    {
        auto& e = s.top();
        switch(e.second)
        {
            case 0:
                e.second = 1;
                if(e.first->left) s.push({e.first->left,0});
                break;
            case 1:
                e.second = 2;
                if(e.first->right) s.push({e.first->right,0});
                break;
            case 2:
                e.second = 3;
                cout << e.first->value << ' ';
                break;
            case 3:
                s.pop();
                break;
        }
    }
}
void CTree::levelorder(CNode* n)
{
    if(!n) return;
    queue<CNode*> q;
    q.push(n);
    while(!q.empty())
    {
        CNode* p = q.front();
        q.pop();
        cout << p->value << ' ';
        if(p->left) q.push(p->left);
        if(p->right) q.push(p->right);
    }
}
int CTree::maxh(CNode* n)
{
    if(!n) return 0;
    int l, r;
    l = maxh(n->left);
    r = maxh(n->right);
    return max(l,r) + 1;
}
void CTree::maxh2(CNode* n, int h, int& mh)
{
    if(!n) return;
    if(h > mh) mh = h;
    maxh2(n->left,h+1,mh);
    maxh2(n->right,h+1,mh);
}
void CTree::print()
{
    inorder(root); //cambiar entre los recorridos para imprimir de distinta manera
    cout << endl;
}
void CTree::print_h()
{
    cout << "Altura: ";
    cout << maxh(root); //cambiar entre los métodos de altura para probar de distinta manera
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
    t.print_h();
    
    return 0;
}
