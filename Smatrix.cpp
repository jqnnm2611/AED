#include <iostream>
using namespace std;

struct CNode
{
    CNode(int v, int a, int b, CNode* d, CNode* n)
    {
        value = v;
        x = a;
        y = b;
        down = d;
        next = n;
    }
    int value;
    int x, y;
    CNode *down, *next;
};

class Smatrix
{
public:
    Smatrix(int r, int c);
    ~Smatrix();
    bool findv(int x, int y, CNode**& pv);
    bool findh(int x, int y, CNode**& ph);
    bool ins(int x, int y, int v);
    bool rem(int x, int y);
    void set(int x, int y, int v);
    int get(int x, int y);

    struct CX
    {
        CX(Smatrix* m, int a, int b);

        CX& operator=(int n);
        operator int();

        int x, y;
        Smatrix* pm;
    };

    CX operator()(int x, int y);

private:
    CNode** rows;
    CNode** cols;
    int nrows, ncols;
};


Smatrix::Smatrix(int r, int c)
{
    nrows = r;
    ncols = c;

    rows = new CNode*[nrows]();
    cols = new CNode*[ncols]();
}

Smatrix::~Smatrix()
{
    for(int i = 0; i < nrows; i++)
    {
        CNode* p = rows[i];

        while(p)
        {
            CNode* aux = p;
            p = p->next;
            delete aux;
        }
    }

    delete[] rows;
    delete[] cols;
}

bool Smatrix::findv(int x, int y, CNode**& pv)
{
    if(x < 0 || x >= ncols || y < 0 || y >= nrows)
    {
        pv = 0;
        return false;
    }

    pv = &cols[x];

    while(*pv && (*pv)->y < y)
        pv = &((*pv)->down);

    return *pv && (*pv)->y == y;
}

bool Smatrix::findh(int x, int y, CNode**& ph)
{
    if(x < 0 || x >= ncols || y < 0 || y >= nrows)
    {
        ph = 0;
        return false;
    }

    ph = &rows[y];

    while(*ph && (*ph)->x < x)
        ph = &((*ph)->next);

    return *ph && (*ph)->x == x;
}

bool Smatrix::ins(int x, int y, int v)
{
    if(x < 0 || x >= ncols || y < 0 || y >= nrows || v == 0)
        return false;

    CNode** pv;
    CNode** ph;

    bool fv = findv(x, y, pv);
    bool fh = findh(x, y, ph);

    if(fv || fh)
        return false;

    CNode* n = new CNode(v, x, y, *pv, *ph);

    *pv = n;
    *ph = n;

    return true;
}

bool Smatrix::rem(int x, int y)
{
    CNode** pv;
    CNode** ph;

    if(!findv(x, y, pv) || !findh(x, y, ph))
        return false;

    CNode* n = *pv;

    if(n != *ph)
        return false;

    *pv = n->down;
    *ph = n->next;

    delete n;

    return true;
}

void Smatrix::set(int x, int y, int v)
{
    CNode** pv;

    if(!findv(x, y, pv))
    {
        if(v != 0)
            ins(x, y, v);

        return;
    }

    if(v == 0)
    {
        rem(x, y);
        return;
    }

    (*pv)->value = v;
}

int Smatrix::get(int x, int y)
{
    CNode** pv;

    if(findv(x, y, pv))
        return (*pv)->value;

    return 0;
}

Smatrix::CX::CX(Smatrix* m, int a, int b)
{
    pm = m;
    x = a;
    y = b;
}

Smatrix::CX& Smatrix::CX::operator=(int n)
{
    pm->set(x, y, n);

    return *this;
}

Smatrix::CX::operator int()
{
    return pm->get(x, y);
}

Smatrix::CX Smatrix::operator()(int x, int y)
{
    return CX(this, x, y);
}

int main()
{
    Smatrix m(5, 5);

    m.set(3, 3, 5);
    m.set(2, 0, 8);
    m.set(1, 4, 12);

    int a = m.get(2, 0);
    cout << a << endl;

    m(3, 3) = 20;

    a = m(3, 3);
    cout << a << endl;

    m(2, 0) = 0;

    a = m(2, 0);
    cout << a << endl;

    return 0;
}
