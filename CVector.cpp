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
	for (int* p = vec, *q = aux; p < vec + size; p++, q++) *q = *p;
	delete vec;
	vec = aux;
	size *= 2;
}

void CVector::collapse() {
	int* aux = new int[size / 2];
	for (int* p = vec, *q = aux; p < vec + size; p++, q++) *q = *p;
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
	if (elem < (size / 2)) collapse();
	for (int* p = vec; p < vec + elem; p++) *p = *(p + 1);
	elem--;
}

void CVector::push_back(int x) {
	if (elem == size) expand();
	*(vec + elem) = x;
	elem++;
}

void CVector::pop_back() {
	if (elem < (size / 2)) collapse();
	elem--;
}

int& CVector::operator[](int i) {
	assert(i < size);
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


int main() {

	CVector v(5);
	v.push_back(3);
	v.push_back(7);
	v.push_back(6);
	v.push_back(1);
	v.push_back(9);
	v.print();
	v.push_back(2);
	v.print();
	v.push_front(5);
	v.push_front(2);
	v.push_front(9);
	v.print();
	v.pop_back();
	v.print();
	v.pop_front();
	v.print();

	return 0;
}
