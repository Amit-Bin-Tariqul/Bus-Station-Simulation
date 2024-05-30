#include <bits/stdc++.h>

template<typename T> bool smaller(const T a, const T b)
{
    return a<=b;
}

template<typename T> class Heap
{
protected:
    unsigned Size, Count;
    T *ara;
    bool (*priority)(const T, const T);

    void heapify(unsigned pos);
    void reverse_heapify(unsigned pos);
    void build();
    void extend();

public:
    Heap();
    Heap(const T[], const int);
    Heap(const std::vector<T>&);

    Heap(bool (*)(const T, const T));
    Heap(const T[], const int, bool (*)(const T, const T));
    Heap(const std::vector<T>&, bool (*)(const T, const T));

    ~Heap();

    void push(const T);
    T pop();
    T top();
    unsigned size();
    bool isEmpty();

    class Empty_Heap{};
};

template<typename T> Heap<T>::Heap(): Size(0), Count(0), priority(smaller)
{}

template<typename T> Heap<T>::Heap(bool (*_priority)(const T, const T)): Size(0), Count(0), priority(_priority)
{}

template<typename T> Heap<T>::Heap(const T inp[], const int s): Size(s>0? s: 0), Count(Size)
{
    if(!Count) return;
    ara=new T[Count];
    for(int i=0; i<Count; ++i) ara[i]=inp[i];
    build();
}

template<typename T> Heap<T>::Heap(const T inp[], const int s, bool (*_priority)(const T, const T)): Size(s>0? s: 0), Count(Size), priority(_priority)
{
    if(!Count) return;
    ara=new T[Count];
    for(int i=0; i<Count; ++i) ara[i]=inp[i];
    build();
}

template<typename T> Heap<T>::Heap(const std::vector<T> &inp): Size(inp.size()), Count(Size)
{
    if(!Count) return;
    ara=new T[Count];
    for(int i=0; i<Count; ++i) ara[i]=inp[i];
    build();
}

template<typename T> Heap<T>::Heap(const std::vector<T> &inp, bool (*_priority)(const T, const T)): Size(inp.size()), Count(Size), priority(_priority)
{
    if(!Count) return;
    ara=new T[Count];
    for(int i=0; i<Count; ++i) ara[i]=inp[i];
    build();
}

template<typename T> void Heap<T>::heapify(unsigned pos)
{
    if(pos>=Count) return;

    unsigned i=pos, l=2*i+1, r=2*i+2;

    if(l<Count) if(priority(ara[l], ara[pos])) pos=l;
    if(r<Count) if(priority(ara[r], ara[pos])) pos=r;

    if(i!=pos)
    {
        std::swap(ara[i], ara[pos]);
        heapify(pos);
    }
}

template<typename T> void Heap<T>::reverse_heapify(unsigned pos)
{
    if(pos>=Count) return;
    if(!pos) return;

    unsigned i=pos, p=(i-1)/2;

    if(priority(ara[i], ara[p])) pos=p;

    if(i!=pos)
    {
        std::swap(ara[i], ara[pos]);
        reverse_heapify(pos);
    }
}

template<typename T> void Heap<T>::build()
{
    for(int i=Count/2; i; --i) heapify(i-1);
}

template<typename T> void Heap<T>::extend()
{
    T temp[Count];
    unsigned i;
    for(i=0; i<Count; ++i) temp[i]=ara[i];

    if(Size)
    {
        delete[] ara;
        Size*=2;
    }
    else Size=1;

    ara=new T[Size];
    for(i=0; i<Count; ++i) ara[i]=temp[i];
}

template<typename T> void Heap<T>::push(const T t)
{
    if(Count==Size) extend();

    ara[Count++]=t;
    reverse_heapify(Count-1);
}

template<typename T> T Heap<T>::pop()
{
    if(!Count) throw Empty_Heap();
    std::swap(ara[0], ara[--Count]);
    heapify(0);
    return ara[Count];
}

template<typename T> T Heap<T>::top()
{
    if(!Count) throw Empty_Heap();
    return ara[0];
}

template<typename T> unsigned Heap<T>::size()
{
    return Count;
}

template<typename T> bool Heap<T>::isEmpty()
{
    return !Count;
}

template<typename T> Heap<T>::~Heap()
{
    delete[] ara;
}
