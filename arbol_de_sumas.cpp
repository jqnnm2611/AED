#include <iostream>
#include <queue>
using namespace std;

struct Nodo {
    Nodo(int v)
    {
        val = v;
        left = right = 0;
    }
    int val;
    Nodo *right, *left;
};

Nodo* crearArbol(int* ini, int* fin)
{
    if (ini == fin) return nullptr;
    queue<Nodo*> q;
    for (int* p = ini; p < fin; ++p) q.push(new Nodo(*p));
    while (q.size() > 1) {
        Nodo* izq = q.front();
        q.pop();
        Nodo* der = q.front();
        q.pop();
        Nodo* padre = new Nodo(izq->val + der->val);
        padre->left = izq;
        padre->right = der;
        q.push(padre);
    }
    return q.front();
}

void inorder(Nodo* n)
{
    if (!n) return;
    inorder(n->left);
    cout << n->val << ' ';
    inorder(n->right);
}

int main()
{
    int n = 16;
    int A[n] = {2, 4, 7, 9, 10, 15, 3, 25, 38, 74, 1, 5, 10, 13, 11, 35};

    Nodo* root = crearArbol(A, A + n);
    inorder(root);

    return 0;
}
