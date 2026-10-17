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
    void inorder_rango(CNode* n, int a, int b);
    void inorder_hojas(CNode* n);
    void inorder_1hijo(CNode* n);
    void borde_izquierdo(CNode* n);
    void borde_derecho(CNode* n);
    void perimetro(CNode* n);
    void extremos_nivel(CNode* n);
    void inorder_impares_rango(CNode* n, int a, int b);
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
void CTree::inorder_rango(CNode* n, int a, int b)
{
    if(!n) return;
    if(n->value > a) inorder_rango(n->left, a, b);
    if(n->value >= a && n->value <= b) cout << n->value << ' ';
    if(n->value < b) inorder_rango(n->right, a, b);
}
void CTree::inorder_hojas(CNode* n)
{
    if(!n) return;
    inorder_hojas(n->left);
    if(!n->left && !n->right) cout << n->value << ' ';
    inorder_hojas(n->right);
}

void CTree::inorder_1hijo(CNode* n)
{
    if(!n) return;
    inorder_1hijo(n->left);
    if((!n->left && n->right) || (n->left && !n->right)) cout << n->value << ' ';
    inorder_1hijo(n->right);
}
void CTree::borde_izquierdo(CNode* n)
{
    if(!n || (!n->left && !n->right)) return;
    cout << n->value << ' ';
    if(n->left) borde_izquierdo(n->left);
    else borde_izquierdo(n->right);
}
void CTree::borde_derecho(CNode* n)
{
    if(!n || (!n->left && !n->right)) return;
    if(n->right) borde_derecho(n->right);
    else borde_derecho(n->left);
    cout << n->value << ' ';
}
void CTree::perimetro(CNode* n)
{
    if(!n) return;
    cout << n->value << ' ';
    if(!n->left && !n->right) return;
    borde_izquierdo(n->left);
    inorder_hojas(n);
    borde_derecho(n->right);
}
void CTree::extremos_nivel(CNode* n)
{
    if(!n) return;
    queue<CNode*> q;
    q.push(n);
    while(!q.empty())
    {
        int cant = q.size();
        for(int aux = 1; aux <= cant; aux++){
            CNode* p = q.front();
            q.pop();
            if (aux == 1 || aux == cant) cout << p->value << ' ';
            if(p->left) q.push(p->left);
            if(p->right) q.push(p->right);
        }
        cout << endl;
    }
}
void CTree::inorder_impares_rango(CNode* n, int a, int b)
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
                if(e.first->left && e.first->value > a)
                    s.push({e.first->left,0});
                break;
            case 1:
                e.second = 2;
                if(e.first->value >= a && e.first->value <= b && e.first->value % 2 != 0)
                    cout << e.first->value << ' ';
                break;
            case 2:
                e.second = 3;
                if(e.first->right && e.first->value < b)
                    s.push({e.first->right,0});
                break;
            case 3:
                s.pop();
                break;
        }
    }
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
