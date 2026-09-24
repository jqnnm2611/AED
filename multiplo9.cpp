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
		int front();
		int back();
		void print();
		void numero();
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
	delete vec;
}

void CVector::expand() {
	int* aux = new int[size * 2];
	for (int* p = vec, *q = aux; p < vec + elem; p++, q++) *q = *p;
	delete vec;
	vec = aux;
	size *= 2;
}

void CVector::collapse() {
	int* aux = new int[size / 2];
	for (int* p = vec, *q = aux; p < vec + elem; p++, q++) *q = *p;
	delete vec;
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
	for (int* p = vec; p < vec + elem; p++) *p = *(p + 1);
	elem--;
	if (elem < (size / 2)) collapse();
}

void CVector::push_back(int x) {
	if (elem == size) expand();
	*(vec + elem) = x;
	elem++;
}

void CVector::pop_back() {
	if (elem == 0) return;
	elem--;
	if (elem < (size / 2)) collapse();
}

int& CVector::operator[](int i) {
	assert(i >= 0 && i < size);
	return *(vec + i);
}

int CVector::front() {
	return *vec;
}

int CVector::back() {
	return *(vec + elem - 1);
}

void CVector::print() {
	for (int* p = vec; p < vec + elem; p++) cout << *p << ' ';
	cout << endl;
}

void CVector::numero() {
    int suma = 0;
    for (int* p = vec; p < vec + elem; p++) suma += *p;
    for (int i = 0; i <= 9; i++){
        if ((suma + i) % 9 == 0){
            if(i == 0 || i == 9) cout << "El dígito que falta es el 0 o el 9";
            else cout << "El dígito que falta es el " << i;
            return;
        }
    }
}


int main() {

	int dig;
	cout << "¿Cuántos dígitos tiene tu número?: ";
	cin >> dig;
	CVector v(dig-1);
	cout << "Ingresa, uno por uno, todos los dígitos menos uno. No importa el orden:" << endl;
	for(int i = 1; i < dig; i++)
	{
	    int x;
        cin >> x;
        v.push_back(x);
	}
	v.numero();
	
	return 0;
}
