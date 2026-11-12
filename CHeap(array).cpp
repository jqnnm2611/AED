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

template <class O>
class CHeap
{
    public:
        CHeap(int t);
        ~CHeap();
        void push(int x);
        void pop();
        void rem(int x);
        int& top();
        bool empty();
        int size();
        void print();
    private:
        int* arr;
        int tam, elem;
};

template <class O>
CHeap<O>::CHeap(int t)
{
    assert(t > 0);
    tam = t;
    elem = 0;
    arr = new int[tam];
}

template <class O>
CHeap<O>::~CHeap()
{
    delete[] arr;
}

template <class O>
void CHeap<O>::push(int x)
{
    if(elem == tam)
    {
        int* aux = new int[tam * 2];
    	for (int* p = arr, *q = aux; p < arr + elem; p++, q++) *q = *p;
    	delete[] arr;
    	arr = aux;
    	tam *= 2;
    }
    
    *(arr + elem) = x;
    elem++;
    
    int i = elem - 1;
    int p = (i - 1) / 2;
    O fun;
    while(i > 0 && fun(arr[i], arr[p]))
    {
        int temp = arr[i];
        arr[i] = arr[p];
        arr[p] = temp;
        i = p;
        p = (i - 1) / 2;
    }
}

template <class O>
void CHeap<O>::pop()
{
    assert(elem > 0);
    int temp = arr[0];
    arr[0] = arr[elem - 1];
    arr[elem - 1] = temp;
    elem--;
    
    int p = 0;
    while (true)
    {
        int l = (p * 2) + 1;
        int r = (p * 2) + 2;
        int val = p;
        
        O fun;
        if (l < elem && fun(arr[l], arr[val])) val = l;
        if (r < elem && fun(arr[r], arr[val])) val = r;
        if (val != p)
        {
            int temp = arr[p];
            arr[p] = arr[val];
            arr[val] = temp;
            p = val;
        }
        else break;
        
    }
}

template <class O>
void CHeap<O>::rem(int x)
{
    assert(elem > 0);
    int pos = 0;
    while(pos < elem && arr[pos] != x) pos++;
    if(pos == elem) return;
    if(pos == 0) 
    {
        pop();
        return;
    }
    if(pos != elem - 1)
    {
        int temp = arr[pos];
        arr[pos] = arr[elem - 1];
        arr[elem - 1] = temp;
    }
    elem--;
    
    O fun;
    int p = (pos - 1) / 2;
    
    if(pos > 0 && fun(arr[pos], arr[p]))
    {
        while(pos > 0 && fun(arr[pos], arr[p]))
        {
            int temp = arr[pos];
            arr[pos] = arr[p];
            arr[p] = temp;
            pos = p;
            p = (pos - 1) / 2;
        }
    }
    else
    {
        while (true)
        {
            int l = (pos * 2) + 1;
            int r = (pos * 2) + 2;
            int val = pos;
            
            if (l < elem && fun(arr[l], arr[val])) val = l;
            if (r < elem && fun(arr[r], arr[val])) val = r;
            if (val != pos)
            {
                int temp = arr[pos];
                arr[pos] = arr[val];
                arr[val] = temp;
                pos = val;
            }
            else break;
            
        }
    }
}

template <class O>
int& CHeap<O>::top()
{
    assert(elem > 0);
    return *arr;
}

template <class O>
bool CHeap<O>::empty()
{
    return elem == 0;
}

template <class O>
int CHeap<O>::size()
{
    return elem;
}

template <class O>
void CHeap<O>::print()
{
	for (int* p = arr; p < arr + elem; p++) cout << *p << ' ';
	cout << endl;
}



int main()
{
    // ==========================================
    //                 MAX HEAP
    // ==========================================

    cout << "========== MAX HEAP ==========" << endl;

    CHeap<mayor> h1(3);

    cout << "Esta vacio? " << h1.empty() << endl;
    cout << "Tamanio: " << h1.size() << endl;

    // PUSH
    cout << "\n--- PUSH ---" << endl;

    h1.push(40);
    h1.push(70);
    h1.push(20);
    h1.push(90);
    h1.push(50);
    h1.push(85);

    cout << "Heap: ";
    h1.print();

    cout << "Tamanio: " << h1.size() << endl;
    cout << "Top: " << h1.top() << endl;

    // REM
    cout << "\n--- REM ---" << endl;

    cout << "Eliminar 70: ";
    h1.rem(70);
    h1.print();

    cout << "Eliminar 20: ";
    h1.rem(20);
    h1.print();

    cout << "Eliminar 999 (inexistente): ";
    h1.rem(999);
    h1.print();

    // POP
    cout << "\n--- POP ---" << endl;

    cout << "Top antes: " << h1.top() << endl;
    h1.pop();

    cout << "Heap despues del pop: ";
    h1.print();

    cout << "Nuevo top: " << h1.top() << endl;
    cout << "Tamanio: " << h1.size() << endl;

    // VACiar heap
    cout << "\n--- VACIAR HEAP ---" << endl;

    while (!h1.empty())
    {
        cout << "Eliminando: " << h1.top() << endl;
        h1.pop();
    }

    cout << "Esta vacio? " << h1.empty() << endl;
    cout << "Tamanio: " << h1.size() << endl;


    // ==========================================
    //                 MIN HEAP
    // ==========================================

    cout << "\n========== MIN HEAP ==========" << endl;

    CHeap<menor> h2(3);

    cout << "Esta vacio? " << h2.empty() << endl;
    cout << "Tamanio: " << h2.size() << endl;

    // PUSH
    cout << "\n--- PUSH ---" << endl;

    h2.push(40);
    h2.push(70);
    h2.push(20);
    h2.push(90);
    h2.push(50);
    h2.push(85);

    cout << "Heap: ";
    h2.print();

    cout << "Tamanio: " << h2.size() << endl;
    cout << "Top: " << h2.top() << endl;

    // REM
    cout << "\n--- REM ---" << endl;

    cout << "Eliminar 70: ";
    h2.rem(70);
    h2.print();

    cout << "Eliminar 85: ";
    h2.rem(85);
    h2.print();

    cout << "Eliminar 999 (inexistente): ";
    h2.rem(999);
    h2.print();

    // POP
    cout << "\n--- POP ---" << endl;

    cout << "Top antes: " << h2.top() << endl;
    h2.pop();

    cout << "Heap despues del pop: ";
    h2.print();

    cout << "Nuevo top: " << h2.top() << endl;
    cout << "Tamanio: " << h2.size() << endl;

    // VACiar heap
    cout << "\n--- VACIAR HEAP ---" << endl;

    while (!h2.empty())
    {
        cout << "Eliminando: " << h2.top() << endl;
        h2.pop();
    }

    cout << "Esta vacio? " << h2.empty() << endl;
    cout << "Tamanio: " << h2.size() << endl;

    return 0;
}

