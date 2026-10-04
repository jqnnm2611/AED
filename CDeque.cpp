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
    int** new_map = new int*[map_size * 2];
    CDeque_iterator aux1, aux2;
    aux1.chunk = new_map + (map_size / 2);
    for(aux2.chunk = start.chunk; aux2.chunk <= finish.chunk; aux1.chunk++, aux2.chunk++)
        *aux1.chunk = *aux2.chunk;
    start.chunk = new_map + (map_size / 2);
    finish.chunk = aux1.chunk - 1;
    delete[] map;
    map = new_map;
    map_size *= 2;
}

void CDeque::push_front(int x)
{
    if(start.offset == *start.chunk)
    {
        if(start.chunk == map) expand_map();
        start.chunk--;
        *start.chunk = new int[chunk_size];
        start.offset = *start.chunk + chunk_size - 1;
    }
    else start.offset--;
    *start.offset = x;
    nelem++;
}

void CDeque::pop_front()
{
    assert(nelem > 0);
    start.offset++;
    if(start.offset == *start.chunk + chunk_size)
    {
        if(start.chunk != finish.chunk)
        {
            delete[] *start.chunk;
            start.chunk++;
            start.offset = *start.chunk;
        }
    }
    nelem--;
}

void CDeque::push_back(int x)
{
    if(finish.offset == *finish.chunk + chunk_size)
    {
        if(finish.chunk == map + map_size - 1) expand_map();
        finish.chunk++;
        *finish.chunk = new int[chunk_size];
        finish.offset = *finish.chunk;
    }
    *finish.offset = x;
    finish.offset++;
    nelem++;
}

void CDeque::pop_back()
{
    assert(nelem > 0);
    finish.offset--;
    if(finish.offset == *finish.chunk)
    {
        if(finish.chunk != start.chunk)
        {
            delete[] *finish.chunk;
            finish.chunk--;
            finish.offset = *finish.chunk + chunk_size;
        }
    }
    nelem--;
}

int& CDeque::operator[](int i)
{
    assert(i >= 0 && i < nelem);
    int primero = *start.chunk + chunk_size - start.offset;
    if(i < primero) return *(start.offset + i);
    i -= primero;
    int** chunk = start.chunk + 1 + i / chunk_size;
    int* offset = *chunk + i % chunk_size;
    return *offset;
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
