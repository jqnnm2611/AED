#include <iostream>
#include <algorithm>
using namespace std;

struct CNode
{
    CNode(int v)
    {
        value = v;
        height = 1;
        left = right = 0;
    }
    int value, height;
    CNode *left, *right;
};

class CAVL
{
public:
    CAVL();
    void ins(int x);
    bool rem(int x);
    bool find(int x);
    void print();

private:
    CNode* root;
    int altura(CNode* p);
    int peso(CNode* p);
    void actualizar(CNode* p);
    CNode* rotarDerecha(CNode* p);
    CNode* rotarIzquierda(CNode* p);
    CNode* balancear(CNode* p);
    CNode* RecInsert(CNode* p, int dato);
    bool RecFind(CNode* p, int dato);
    bool brep;
    CNode** rep(CNode** p);
    CNode* RecRemove(CNode* p, int dato, bool& eliminado);
    void inorder(CNode* p);
    void RecPrint(CNode* p, int nivel);
};

CAVL::CAVL()
{
    root = 0;
    brep = 0;
}

int CAVL::altura(CNode* p)
{
    return p ? p->height : 0;
}

int CAVL::peso(CNode* p)
{
    return altura(p->left) - altura(p->right);
}

void CAVL::actualizar(CNode* p)
{
    p->height = 1 + max(altura(p->left), altura(p->right));
}

CNode* CAVL::rotarDerecha(CNode* p)
{
    CNode* aux_new  = p->left;
    CNode* aux_hijo = aux_new->right;
    aux_new->right = p;
    p->left = aux_hijo;
    actualizar(p);
    actualizar(aux_new);
    return aux_new;
}

CNode* CAVL::rotarIzquierda(CNode* p)
{
    CNode* aux_new  = p->right;
    CNode* aux_hijo = aux_new->left;
    aux_new->left = p;
    p->right = aux_hijo;
    actualizar(p);
    actualizar(aux_new);
    return aux_new;
}

CNode* CAVL::balancear(CNode* p)
{
    actualizar(p);
    if(peso(p) > 1)
    {
        if(peso(p->left) < 0) p->left = rotarIzquierda(p->left);
        return rotarDerecha(p);
    }
    if(peso(p) < -1)
    {
        if(peso(p->right) > 0) p->right = rotarDerecha(p->right);
        return rotarIzquierda(p);
    }
    return p;
}

CNode* CAVL::RecInsert(CNode* p, int dato)
{
    if(!p) return new CNode(dato);
    else if(dato < p->value) p->left = RecInsert(p->left, dato);
    else if(dato > p->value) p->right = RecInsert(p->right, dato);
    else return p;
    return balancear(p);
}

CNode** CAVL::rep(CNode** p)
{
    CNode** q = p;
    if(brep == 1)
    {
        q = &((*q)->right);
        while((*q)->left)
            q = &((*q)->left);
    }
    else
    {
        q = &((*q)->left);
        while((*q)->right)
            q = &((*q)->right);
    }
    brep = !brep;
    return q;
}

CNode* CAVL::RecRemove(CNode* p, int dato, bool& eliminado)
{
    if(!p) return 0;
    if(dato < p->value)
        p->left = RecRemove(p->left, dato, eliminado);
    else if(dato > p->value)
        p->right = RecRemove(p->right, dato, eliminado);
    else
    {
        eliminado = true;
        if(!p->left || !p->right)
        {
            CNode* aux = p->left ? p->left : p->right;
            delete p;
            return aux;
        }
        bool derecha = brep;
        CNode** q = rep(&p);
        int valor = (*q)->value;
        p->value = valor;
        if(derecha)
            p->right = RecRemove(p->right, valor, eliminado);
        else
            p->left = RecRemove(p->left, valor, eliminado);
    }
    return balancear(p);
}

bool CAVL::RecFind(CNode* p, int dato)
{
    if(!p) return 0;
    if(p->value == dato) return 1;
    return dato < p->value ? RecFind(p->left, dato) : RecFind(p->right, dato);
}

void CAVL::inorder(CNode* p)
{
    if(!p) return;
    inorder(p->left);
    cout << p->value << " ";
    inorder(p->right);
}

void CAVL::RecPrint(CNode* p, int nivel)
{
    if(!p) return;
    RecPrint(p->right, nivel + 1);
    for(int i = 0; i < nivel; i++) cout << "    ";
    cout << p->value << "(h" << p->height << ")" << endl;
    RecPrint(p->left, nivel + 1);
}

void CAVL::ins(int x)
{
    root = RecInsert(root, x);
}

bool CAVL::rem(int x)
{
    bool eliminado = false;
    root = RecRemove(root, x, eliminado);
    return eliminado;
}

bool CAVL::find(int x)
{
    return RecFind(root, x);
}

void CAVL::print()
{
    cout << "Impresión inorder: ";
    inorder(root);
    cout << endl;
    cout << "----------------" << endl;
    RecPrint(root, 0);
    cout << "----------------" << endl;
}


int main()
{
    CAVL t;
    int datos[] = {30, 20, 10, 40, 50, 25};
    for(int x : datos)
    {
        cout << "Insertando: " << x << endl;
        t.ins(x);
        t.print();
    }
    cout << "Buscar 25: " << t.find(25) << endl;
    cout << "Buscar 99: " << t.find(99) << endl;
    
    cout << "\nEliminar 10: " << t.rem(10) << endl;
    t.print();
    
    cout << "\nEliminar 30: " << t.rem(30) << endl;
    t.print();
    
    cout << "\nEliminar 99: " << t.rem(99) << endl;
    t.print();
    return 0;
}
