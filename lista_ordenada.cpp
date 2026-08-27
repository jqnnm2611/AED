#include <iostream>
using namespace std;

template<class T>
class asc {
public:
    bool operator()(T a, T b) {
        return a > b;
    }
};

template<class T>
class desc {
public:
    bool operator()(T a, T b) {
        return a < b;
    }
};

template<class T, class O, int n = 10>
class list_ord {
    int tam = n;
    int elem = 0;
    T arr[n];
    O fun;
public:
    T* binarySearch(T e) {
        T* low = arr;
        T* high = arr + elem - 1;
        while (low <= high) {
            T* mid = low + (high - low) / 2;
            if (*mid == e)
                return mid;
            if (fun(e, *mid))
                low = mid + 1;
            else
                high = mid - 1;
        }
        return nullptr;
    }
    T* encontrar(T e) {
        T* low = arr;
        T* high = arr + elem;
        while (low < high) {
            T* mid = low + (high - low) / 2;
            if (fun(e, *mid))
                low = mid + 1;
            else
                high = mid;
        }
        return low;
    }
    bool add(T e) {
        if (elem == tam) return false;
        T* aux = encontrar(e);
        for (T* p = arr + elem; p > aux; p--) *p = *(p - 1);
        *aux = e;
        elem++;
        return true;
    };
    bool del(T e) {
        if (elem == 0) return false;
        T* aux = binarySearch(e);
        if (aux == nullptr) return false;
        for (T* p = aux; p < arr + elem - 1; p++) *p = *(p + 1);
        elem--;
        return true;
    };
    void print() {
        cout << "Lista: " << endl;
        for (T* p = arr; p < arr + elem; p++) cout << *p << ' ';
        cout << endl;
    };

};


int main()
{

    list_ord<int, asc<int>, 15> lista;
    lista.add(3);
    lista.add(6);
    lista.add(1);
    lista.add(7);
    lista.add(8);
    lista.add(2);
    lista.add(13);
    lista.print();
    lista.del(1);
    lista.del(8);
    lista.del(6);
    lista.print();

    return 0;
}
