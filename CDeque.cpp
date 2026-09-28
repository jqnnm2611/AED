#include <iostream>
#include <assert.h>
using namespace std;

struct CDeque_iterator
{
    int** chunk;
    int*  offset;
};

class CDeque
{
public:
    CDeque(int cs, int ms);
    ~CDeque();
    void expand_map();
    void push_front(int x);
    void pop_front();
    void push_back(int x);
    void pop_back();
    int& operator[](int i);
    int& front();
    int& back();
    void print();
    
private:
    int** map;
    int chunk_size, map_size;
    int nelem;
    CDeque_iterator start, finish;
};

CDeque::CDeque(int cs, int ms)
{
    chunk_size = cs;
    map_size = ms;
    map = new int*[map_size];

    start.chunk = finish.chunk = map + map_size / 2;
    *start.chunk = new int[chunk_size];

    start.offset = finish.offset = *start.chunk + chunk_size / 2;

    nelem = 0;
}

CDeque::~CDeque()
{
    for ( int** c = start.chunk; c <= finish.chunk; ++c )
        delete[] *c;
    delete[] map;
}

void CDeque::expand_map()
{
}

void CDeque::push_front(int x)
{
}

void CDeque::pop_front()
{
}

void CDeque::push_back(int x)
{
    *finish.offset = x;
    finish.offset++;
    if(finish.offset == *finish.chunk + chunk_size)
    {
        if(finish.chunk == map + map_size - 1) expand_map();
        finish.chunk++;
        *finish.chunk = new int[chunk_size];
        finish.offset = *finish.chunk;
    }
    nelem++;
}

void CDeque::pop_back()
{
}

int& CDeque::operator[](int i)
{
}

int& CDeque::front()
{
    return *start.offset;
}

int& CDeque::back()
{
    return *(finish.offset - 1);
}

void CDeque::print()
{
    for ( int** c = start.chunk; c <= finish.chunk; ++c )
    {
        int* begin = ( c == start.chunk )  ? start.offset  : *c;
        int* end   = ( c == finish.chunk ) ? finish.offset : *c + chunk_size;

        for ( int* p = begin; p != end; ++p )
            std::cout << *p << " ";
    }
    std::cout << "\n";
}

int main()
{
    CDeque v(5, 7); 
    v.push_back(3);
    v.push_back(7);
    v.push_back(6);
    v.push_front(1);
    v.push_front(9);
    v.push_front(2);
    v.print();
        
    v[3] = 4;
    v.print();
    
    v.front() = 1;
    v.back() = 1;
    v.print();

    
    v.pop_back();
    v.pop_front();
    v.print();

    v.pop_back();
    v.pop_front();
    v.print();

    v.pop_back();
    v.pop_front();
    v.print();
    
    cout<<endl;
}
