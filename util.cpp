#include <iostream>
using namespace std;


template<class O>
struct util {
	O fun;
	void split(int* ini, int* fin) {
		int* p = ini;
		while (p <= fin) {
			if (!fun(*p)) p++;
			else {
				for (int* q = p; q > ini; q--) swap(*q, *(q-1));
				ini++;
			}
		}
	}
	void merge(int* ini, int* mid, int* fin) {
		while (mid < fin) {
			if (*ini <= *mid) ini++;
			else {
				for (int* p = mid; p > ini; p--) swap(*p, *(p - 1));
			}
			mid++;
		}
	}
};

class div3 {
public:
	bool operator()(int a) {
		return !(a % 3);
	}
};

int main() {

	int arr[10] = {1,4,7,8,21,3,4,5,6,9};
	for (int* p = arr; p < arr + 10; p++) cout << *p << ' ';
	cout << endl;
	util<div3> u;
	//u.split(arr, arr + 9);
	u.merge(arr, arr+5, arr+9);

	for (int* p = arr; p < arr + 10; p++) cout << *p << ' ';

}
