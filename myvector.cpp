#include "myvector.h"

MyVector::MyVector (const MyVector& arg)
    :sz {arg.sz},
     elem {new double[arg.sz]}
{
    copy(arg.elem,arg.elem+sz,elem);//    copy(arg,arg`+sz,elem);
}

MyVector& MyVector::operator= (const MyVector& v)
{
    double* p = new double[v.sz];
    copy (v.elem, v.elem+v.sz, p);
    delete[] elem;
    elem = p;
    sz = v.sz;
    return *this;
}

MyVector::MyVector (MyVector&& a)
    :sz {a.sz},
     elem {a.elem}
{
    a.sz = 0;
    a.elem = nullptr;
}

MyVector& MyVector::operator= (MyVector&& a)
{
    delete[] elem;
    elem = a.elem;
    sz = a.sz;
    a.sz = 0;
    a.elem = nullptr;
    return *this;
}
