#ifndef MYVECTOR_H
#define MYVECTOR_H
#include <iostream>
#include<algorithm>
#include <memory>
#include <initializer_list>
#include <iterator>
using namespace std;



template <typename T, typename A>
struct Vector_base
{
    using size_type = size_t;
    A alloc;
    T* elem;
    size_type sz;
    size_type space;
    
    Vector_base (A a, size_type n)
        : alloc {a}, elem {a.allocate(n)}, sz {n}, space {n}{}
    
    ~Vector_base() {
        alloc.deallocate(elem, space);
    }
};

//end of class Vector_base

//class MyVector

template<typename T, typename A = allocator<T>>
class MyVector : private Vector_base<T,A>
{
public:
    using size_type = typename Vector_base<T,A>::size_type;

    explicit MyVector(size_type n, T d = T(), A alloc = A());
    
    MyVector(initializer_list<T> lst, const A& alloc = A());
    
    MyVector (const A& alloc = A()): Vector_base<T, A> (alloc,0){}
    
    MyVector (const MyVector& arg);
    MyVector& operator= (const MyVector& v);
    
    MyVector (MyVector&& a);
    MyVector& operator= (MyVector&& a);
    
    ~MyVector();
    
    T& at (size_type n);
    const T& at (size_type n) const;
    
    T& operator[] (size_type n);
    const T& operator[] (size_type n) const;
    
    size_type size () const {return this->sz;}
    
    size_type capacity() const { return this->space;}
    
    void reserve (size_type newalloc);
    
    void resize (size_type& newsize, T val = T());
    
    void push_back (const T& d);
};

template <typename T, typename A>
MyVector<T,A>::MyVector(size_type n, T d, A alloc)
    :Vector_base<T, A> (alloc, n)
{
    for (size_type i=0; i<n; ++i)
        this->alloc.construct(&this->elem[i], d);
}

template <typename T, typename A>
MyVector<T,A>::MyVector(initializer_list<T> lst, const A& alloc)
    :Vector_base<T, A> (alloc, lst.size())
{
    for (size_type i=0; i<lst.size(); ++i)
        this->alloc.construct(&this->elem[i],*(lst.begin()+i));
}

template <typename T, typename A>
MyVector<T,A>::~MyVector()
{
    for (size_type i = 0; i<this->sz; ++i)
        this->alloc.destroy(this->elem+i);
}

template <typename T, typename A>
MyVector<T,A>::MyVector(const MyVector& arg)
    :Vector_base<T,A>(arg.alloc,arg.sz)
{
    for (size_type i=0; i<arg.sz; ++i)
        this->alloc.construct(&this->elem[i], arg[i]);
}

template <typename T, typename A>
MyVector<T, A>& MyVector<T, A>::operator=(const MyVector<T, A>& arg)
{
    if (this == &arg)
        return *this;
    Vector_base<T, A> b (this->alloc, arg.sz);
    uninitialized_copy(&arg[0], &arg[arg.size()], b.elem);
    swap(this->elem, b.elem);
    swap(this->sz, b.sz);
    swap(this->space, b.space);
    for (size_type i = 0; i < b.sz; ++i)
        b.alloc.destroy(b.elem + i);//free memory used for vector before
    return *this;
}

template <typename T, typename A>
MyVector<T,A>::MyVector(MyVector&& arg)
    :Vector_base<T,A>(arg.alloc,arg.sz)
{
    arg.sz=0;
    arg.elem=nullptr;
    arg.space=0;
    std::cout<<endl<<"yes"<<endl<<endl;
}

template <typename T, typename A>
MyVector<T, A>& MyVector<T, A>::operator=(MyVector<T, A>&& arg)
{
    swap(this->elem, arg.elem);
    swap(this->sz, arg.sz);
    swap(this->space, arg.space);
    delete[] arg.elem;
    std::cout<<endl<<"yes"<<endl<<endl;
    return *this;
}

template <typename T, typename A>
void MyVector<T,A>::reserve(size_type newalloc)
{
    if (newalloc <= this->space) return;
    Vector_base<T,A> b (this->alloc, newalloc);
    uninitialized_copy (&this->elem[0], &this->elem[this->sz], b.elem);
    for (size_type i = 0; i < this->sz; ++i)
    {
        this->alloc.destroy (&this->elem[i]);
    }
    b.sz = this->sz;
    swap(this->elem, b.elem);
    swap(this->sz, b.sz);
    swap(this->space, b.space);
}

template <typename T, typename A>
void MyVector<T,A>::push_back (const T& val)
{
    if (!(this->space))
        reserve(8);
    else if (this->sz == this->space)
        reserve(2 * this->space);
    this->alloc.construct(&this->elem[this->sz], val);
    ++this->sz;
}

template <typename T, typename A>
void MyVector<T,A>::resize (size_type& newsize, T val)
{
    reserve (newsize);
    for (size_type i = this->sz; i < newsize; ++i) this->alloc.construct (&this->elem[i], val);
    for (size_type i = newsize; i < this->sz; ++i) this->alloc.destroy (&this->elem[i]);
    this->sz = newsize;
}

template <typename T, typename A>
T& MyVector<T,A>::at (size_type n)
{
    if (n < 0 || this->sz <= n) throw out_of_range("Out of range");
    return this->elem[n];
}

template <typename T, typename A>
const T& MyVector<T,A>::at (size_type n) const
{
    if (n < 0 || this->sz <= n) throw out_of_range("Out of range");
    return this->elem[n];
}

template <typename T, typename A>
T& MyVector<T,A>::operator[] (size_type n)
{
    return this->elem[n];
}

template <typename T, typename A>
const T& MyVector<T,A>::operator[] (size_type n) const
{
    return this->elem[n];
}

template <class T>
void print(const MyVector<T> &src)
{
    for (auto i = 0; i < src.size(); ++i) {
        cout << src[i] << " ";
    }
    cout << endl;
}


//end of class MyVector

#endif // MYVECTOR_H
