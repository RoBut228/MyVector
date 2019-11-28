#ifndef MYVECTOR_H
#define MYVECTOR_H
#include <iostream>
#include<algorithm>
using namespace std;

class MyVector
{
public:
    explicit MyVector(unsigned long long s)
        :sz {s},
         elem {new double[s]}
    {
        for (unsigned long long i=0; i<sz; ++i)
            elem[i]=0;
    }
    MyVector(initializer_list<double> lst)
        :sz {lst.size()},
         elem {new double[sz]}
    {
        copy(lst.begin(), lst.end(), elem);
    }
    MyVector (const MyVector& a);
    MyVector& operator= (const MyVector&);
    double& operator[] (unsigned long long n) {return elem[n];}
    double operator[] (unsigned long long n) const {return elem[n];}
    MyVector (MyVector&& a);
    MyVector& operator= (MyVector&&);
    ~MyVector()
    {
        delete[] elem;
    }
    unsigned long long size() const {return sz;}
    double get(unsigned long long n) const { return elem[n];}
    void set(unsigned long long n, double v) { elem[n]=v; }

private:
    unsigned long long sz;
    double* elem;
};

#endif // MYVECTOR_H
