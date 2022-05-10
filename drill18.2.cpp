#include "std_lib_facilities.h"
 //Define a global vector<int> gv; initialize it with ten ints
vector<int> gv{ 1, 2, 4, 8, 16, 32, 64, 128, 256, 512 };
// Define a function f() taking a vector<int> argument.
void f(vector<int> v)
{
    
    vector<int> lv(v.size());
//Copy the values from v into lv
    lv = v;

    for (int i = 0; i < lv.size(); i++)
    {
 //     Print out the elements of lv. 
        cout << lv[i] << " ";
    }

    cout << endl;
//Copy the values from v into lv2
    vector<int> lv2 = v;

    for (int i = 0; i < lv2.size(); i++)
    {
 //     Print out the elements of lv2       
        cout << lv2[i] << " ";
    }

    cout << endl;

}
 
int main()
{
 //   Call f() with gv as its argument.
    f(gv);
 //Define a vector<int> vv, and initialize it with the first ten factorial values
    vector<int> vv(10);

    int x = 1;
// Call f() with vv as its argument
    for (int i = 0; i < 10; i++)
    {
        x = x * (i + 1);
        vv[i] = 1 * x;
    }

    f(vv);

    return 0;

}
