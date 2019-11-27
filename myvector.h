#ifndef MYVECTOR_H
#define MYVECTOR_H


class MyVector
{
public:
    MyVector(int s)
        :sz {s},
         elem {new double[s]}
    {
        for (int i=0; i<sz; ++i)
            elem[i]=0;
    }
    ~MyVector()
    {
        delete[] elem;
    }
    int size() const {return sz;}
    double get(int n) const { return elem[n];}
    void set(int n, double v) { elem[n]=v; }
private:
    int sz;
    double* elem;
};

#endif // MYVECTOR_H
