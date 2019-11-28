#include "myvector.h"
#include <vector>
#include <cmath>


int main()
{
    MyVector a {1,2,3,4,5};
    MyVector b {10,9,8,7,6,5,4,3,2};
    for (unsigned long long i=0; i<b.size(); ++i)
    {
        cout<<b[i]<<endl;
    }
    b = a;
    for (unsigned long long i=0; i<b.size(); ++i)
    {
        cout<<b[i]<<endl;
    }
}

