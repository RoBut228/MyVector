#include <iostream>
#include "myvector.h"

using namespace std;

int main()
{
    MyVector c(20);
    int s{0};
    for(int i=0; i<20; ++i)
    {
        c.set(i,i*i*i);
    }
    for(int i=0; i<19; ++i)
    {
        c.set(i,c.get(i)+c.get(i+1));
        cout<<c.get(i)<<endl;
    }
}
