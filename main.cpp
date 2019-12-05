#include "myvector.h"
#include <vector>
#include <cmath>
#include <windows.h>


int main()
{
    size_t i = 0;
    while(true)
    {
        MyVector<string> d(10000);
        for (int j=0;j<10000;++j)
        {
            std::string s = std::string(1000, 't');
            d[j]=s;

           cout<<d[j]<<endl;
        }
      //  ++i;
    //    cout<<endl<<endl<<"Number of try : "<<i<<endl<<endl<<endl;
     //   Sleep(1000);
    }
}

