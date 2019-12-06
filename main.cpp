#include "myvector.h"
#include <vector>
#include <cmath>
#include <windows.h>

using vec_int = MyVector<int>;

vec_int test ()
{
    vec_int a{1,2,3,4};
    return a;
}

void test2 (vec_int f)
{
    print(f);
}


int main()
{
      MyVector<int> t(10);
      cout << "MyVector 't' default\n";
      print(t);

      MyVector<int> a{0, 1, 2, 3};
      a.push_back(0);

      cout << "MyVector 'a' initializer_list and push_back\n";
      print(a);

      MyVector<int> b{a};

      MyVector<int> c;

      cout << "MyVector 'b' copy constructor:\n";
      print(b);

       c = move(b);

      cout << "MyVector 'c' values after move \n";
      print(c);


      vec_int te = test();
      test2(std::move(te));

      print(te);


//      while (true)
//      {
//          MyVector<string> d;
//          string s = string (10000,'q');
//          for (size_t i = 0; i < 10000; ++i)
//          {
//              d.push_back(s);
//          }
//      }
}

