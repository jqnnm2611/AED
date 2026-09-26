#include <iostream>
#include <assert.h>
using namespace std;


class CVector {
public:
    CVector(int s);
    ~CVector();
    void push_front(int x);
    void pop_front();
    void push_back(int x);
    void pop_back();
    void expand();
    void collapse();
    int& operator[](int i);
    int* front();
    int back();
    int getElem();
    bool empty();
    void print();
private:
    int* vec;
    int size, elem;
};


CVector::CVector(int s) {
    size = s;
    elem = 0;
    vec = new int[size];
}


CVector::~CVector() {
    delete[] vec;
}


void CVector::expand() {
    int* aux = new int[size * 2];
    for (int* p = vec, *q = aux; p < vec + elem; p++, q++) *q = *p;
    delete[] vec;
    vec = aux;
    size *= 2;
}


void CVector::collapse() {
    if (size <= 1) return;
    int* aux = new int[size / 2];
    for (int* p = vec, *q = aux; p < vec + elem; p++, q++) *q = *p;
    delete[] vec;
    vec = aux;
    size /= 2;
}


void CVector::push_front(int x) {
    if (elem == size) expand();
    for (int* p = vec + elem; p > vec; p--) *p = *(p - 1);
    *vec = x;
    elem++;
}


void CVector::pop_front() {
    if (elem == 0) return;
    for (int* p = vec; p < vec + elem - 1; p++) *p = *(p + 1);
    elem--;
    if (elem < size / 2) collapse();
}


void CVector::push_back(int x) {
    if (elem == size) expand();
    *(vec + elem) = x;
    elem++;
}


void CVector::pop_back() {
    if (elem == 0) return;
    elem--;
    if (elem < size / 2) collapse();
}


int& CVector::operator[](int i) {
    assert(i >= 0 && i < elem);
    return *(vec + i);
}


int* CVector::front() {
    return vec;
}


int CVector::back() {
    return *(vec + elem - 1);
}


int CVector::getElem() {
    return elem;
}


bool CVector::empty() {
    return elem == 0;
}


void CVector::print() {
    for (int* p = vec; p < vec + elem; p++) cout << (char)*p << ' ';
    cout << endl;
}


bool esOperador(int x) {
    return x == '+' || x == '-' || x == '*' || x == '/';
}


int prioridad(int x) {
    if (x == '+' || x == '-') return 1;
    if (x == '*' || x == '/') return 2;
    return 0;
}


int main() {

    CVector entrada(10);

    entrada.push_back('(');
    entrada.push_back('3');
    entrada.push_back('+');
    entrada.push_back('5');
    entrada.push_back(')');
    entrada.push_back('*');
    entrada.push_back('(');
    entrada.push_back('7');
    entrada.push_back('-');
    entrada.push_back('4');
    entrada.push_back(')');

    CVector pila(5);
    CVector salida(10);

    for (int* p = entrada.front(); p < entrada.front() + entrada.getElem(); p++) {
        int x = *p;
        if (x == '(') pila.push_back(x);
        else if (x == ')') {
            while (!pila.empty() && pila.back() != '(') {
                salida.push_back(pila.back());
                pila.pop_back();
            }
            if (!pila.empty())
                pila.pop_back();
        }
        else if (esOperador(x)) {
            while (!pila.empty() && pila.back() != '(' && prioridad(x) <= prioridad(pila.back())) {
                salida.push_back(pila.back());
                pila.pop_back();
            }
            pila.push_back(x);
        }
        else salida.push_back(x);
    }

    while (!pila.empty()) {
        salida.push_back(pila.back());
        pila.pop_back();
    }

    cout << "Infija: ";
    entrada.print();
    cout << "Postfija: ";
    salida.print();

    return 0;
}
