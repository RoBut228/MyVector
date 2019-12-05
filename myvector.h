#ifndef MYVECTOR_H
#define MYVECTOR_H
#include <iostream>
#include<algorithm>
#include <memory>
#include <initializer_list>
#include <iterator>
using namespace std;

//class Vector_base

template <typename T, typename A>
struct Vector_base
{
    A alloc;
    T* elem;
    size_t sz;
    size_t space;
    
    Vector_base (A a, size_t n)
        : alloc {a}, elem {a.allocate(n)}, sz {n}, space {n}{}

    Vector_base(Vector_base&& arg);

    Vector_base& operator=(Vector_base&& arg);
    
    ~Vector_base() {alloc.deallocate(elem, space);}
};

template <typename T, typename A>
Vector_base<T,A>::Vector_base(Vector_base&& arg)
{
    arg.sz=0;
    arg.elem=nullptr;
    arg.space=0;
}

template <typename T, typename A>
Vector_base<T,A>& Vector_base<T,A>::operator=(Vector_base&& arg)
{
    swap(this->elem, arg.elem);
    swap(this->sz, arg.sz);
    swap(this->space, arg.space);
    return *this;
}

//end of class Vector_base

//class MyVector

template<typename T, typename A = allocator<T>>
class MyVector : private Vector_base<T,A>
{
public:
    explicit MyVector(size_t n, T d = T(), A alloc = A());
    
    MyVector(initializer_list<T> lst, const A& alloc = A());
    
    MyVector (const A& alloc = A()): Vector_base<T, A> (alloc,1){}
    
    MyVector (const MyVector& arg);
    MyVector& operator= (const MyVector& v);
    
    MyVector (MyVector&& a) = default;
    MyVector& operator= (MyVector&& a) = default;
    
    ~MyVector();
    
    T& at (size_t n);
    const T& at (size_t n) const;
    
    T& operator[] (size_t n);
    const T& operator[] (size_t n) const;
    
    size_t size () const {return this->sz;}
    
    size_t capacity() const { return this->space;}
    
    void reserve (size_t newalloc);
    
    void resize (size_t& newsize, T val = T());
    
    void push_back (const T& d);
};

template <typename T, typename A>
MyVector<T,A>::MyVector(size_t n, T d, A alloc)
    :Vector_base<T, A> (alloc, n)
{
    for (int i=0; i<n; ++i)
        this->alloc.construct(&this->elem[i], d);
}

template <typename T, typename A>
MyVector<T,A>::MyVector(initializer_list<T> lst, const A& alloc)
    :Vector_base<T, A> (alloc, lst.size())
{
    for (int i=0; i<lst.size(); ++i)
        this->alloc.construct(&this->elem[i],*(lst.begin()+1));
}

template <typename T, typename A>
MyVector<T,A>::~MyVector()
{
    for (int i = 0; i<this->sz; ++i)
        this->alloc.destroy(this->elem+i);
}

template <typename T, typename A>
MyVector<T,A>::MyVector(const MyVector& arg)
    :Vector_base<T,A>(arg.alloc,arg.sz)
{
    for (int i=0; i<arg.sz; ++i)
        this->alloc.construct(&this->elem[i], arg[i]);
}

template <typename T, typename A>
MyVector<T, A>& MyVector<T, A>::operator=(const MyVector<T, A>& arg)
{
    if (this == &arg)
        return *this;
    Vector_base<T, A> b{ this->alloc, arg.sz };
    uninitialized_copy(arg.begin(), arg.end(), b.elem);
    swap(this->elem, b.elem);
    swap(this->sz, b.sz);
    swap(this->space, b.space);
    for (size_t i = 0; i < b.sz; ++i)
        b.alloc.destroy(b.elem + i);//free memory used for vector before
    return *this;
}

template <typename T, typename A>
void MyVector<T,A>::reserve(size_t newalloc)
{
    if (newalloc <= this->space) return;
    Vector_base<T,A> b (this->alloc, newalloc);
    uninitialized_copy (b.elem, &b.elem[this->sz], this->elem);
    for (size_t i = 0; i < this->sz; ++i)
    {
        this->alloc.destroy (&this->elem[i]);
    }
    swap (this->sz,b.sz);
    swap (this->space,b.space);
    swap (this->alloc,b.alloc);
    swap (this->elem,b.elem);
}

template <typename T, typename A>
void MyVector<T,A>::push_back (const T& val)
{
    if (!this->space)
    reserve(8);
    else if (this->sz == this->space)
    reserve(2 * this->space);
    this->alloc.construct(&this->elem[this->sz], val);
    ++this->sz;
}

template <typename T, typename A>
void MyVector<T,A>::resize (size_t& newsize, T val)
{
    reserve (newsize);
    for (size_t i = this->sz; i < newsize; ++i) this->alloc.construct (&this->elem[i], val);
    for (size_t i = newsize; i < this->sz; ++i) this->alloc.destroy (&this->elem[i]);
    this->sz = newsize;
}

template <typename T, typename A>
T& MyVector<T,A>::at (size_t n)
{
    if (n < 0 || this->sz <= n) throw out_of_range("Out of range");
    return this->elem[n];
}

template <typename T, typename A>
const T& MyVector<T,A>::at (size_t n) const
{
    if (n < 0 || this->sz <= n) throw out_of_range("Out of range");
    return this->elem[n];
}

template <typename T, typename A>
T& MyVector<T,A>::operator[] (size_t n)
{
    return this->elem[n];
}

template <typename T, typename A>
const T& MyVector<T,A>::operator[] (size_t n) const
{
    return this->elem[n];
}

//end of class MyVector

#endif // MYVECTOR_H
