#include <iostream>
#include <assert.h>
using namespace std;


template <class T>
struct CNode
{
    CNode(T v)
    {
        value = v;
        next = 0;
    }

    T value;
    CNode<T>* next;
};

template <class T>
class Circular_list
{
public:
    Circular_list(int n);
    ~Circular_list();
    void push_back(T x);
    void kill(int n);
    void print();

private:
    CNode<T>* head;
    CNode<T>* tail;
    int elem;
};

template <class T>
Circular_list<T>::Circular_list(int n)
{
    head = 0;
    tail = 0;
    elem = 0;

    cout << "Ingrese las letras: ";
    for(int i = 0; i < n; i++)
    {
        T x;
        cin >> x;
        push_back(x);
    }
}

template <class T>
Circular_list<T>::~Circular_list()
{
    if(elem == 0) return;
    tail->next = 0;
    while(head)
    {
        CNode<T>* t = head;
        head = head->next;
        delete t;
    }
}

template <class T>
void Circular_list<T>::push_back(T x)
{
    CNode<T>* t = new CNode<T>(x);
    if(elem == 0)
    {
        head = tail = t;
        tail->next = head;
    }
    else
    {
        t->next = head;
        tail->next = t;
        tail = t;
    }
    elem++;
}

template <class T>
void Circular_list<T>::kill(int n)
{
    assert(n > 0);
    if(elem == 0) return;
    CNode<T>* p = head;
    CNode<T>* prev = tail;
    int cont = 1;
    while(elem > 0)
    {
        if(cont == n)
        {
            cout << p->value << ' ';
            if(elem == 1)
            {
                delete p;
                head = 0;
                tail = 0;
                elem = 0;
            }
            else
            {
                prev->next = p->next;
                if(p == head) head = p->next;
                if(p == tail) tail = prev;
                delete p;
                p = prev->next;
                elem--;
            }
            cont = 1;
        }
        else
        {
            prev = p;
            p = p->next;
            cont++;
        }
    }
    cout << endl;
}

template <class T>
void Circular_list<T>::print()
{
    if(elem == 0)
    {
        cout << endl;
        return;
    }
    CNode<T>* p = head;
    for(int i = 0; i < elem; i++)
    {
        cout << p->value << ' ';
        p = p->next;
    }
    cout << endl;
}

int main()
{
    int n;
    cout << "Cantidad de letras: ";
    cin >> n;
    Circular_list<char> lista(n);

    int k;
    cout << "Numero de kill: ";
    cin >> k;

    cout << "Lista inicial: ";
    lista.print();

    cout << "Orden de eliminacion: ";
    lista.kill(k);

    return 0;
}
