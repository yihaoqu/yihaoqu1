#include "std_lib_facilities.h"
//difine an int array ga of ten ints
int ga[10]{ 1, 2, 4, 8, 16, 32, 64, 128, 256, 512 };

//define a function taking an int array argument and a argument indicating the number of elements in array.
void f(int a[], int x)
//define a local int array la of  ten ints 
{
   
    int la[10];
//copy the values form ga to la 
    for (int i = 0; i < 10; i++)
    {
        la[i] = a[i];
    }
//  Print out the elements of la
    for (int i = 0; i < 10; i++)
    {
        cout << la[i] << " ";
    }

    cout << endl;
 // Define a pointer p to int
    int* p = new int[10];
//Copy the values from the argument array into the free-store array.
    for (int i = 0; i < 10; i++)
    {
        p[i] = a[i];
    }
// Print out the elements of the free-store array
    for (int i = 0; i < 10; i++)
    {
        cout << p[i] << " ";
    }

    cout << endl;
//Deallocate the free-store array.
    delete[] p;
}
 //In main(),Call f() with ga as its argument
 
int main()
{
    f(ga, 10);
 //Define an array aa with ten elements, and initialize it with the first ten factorial values
    int aa[10];

    int x = 1;

    for (int i = 0; i < 10; i++)
    {
        x = x * (i + 1);
        aa[i] = 1 * x;
    }
 //Call f() with aa as its argument
    f(aa, 10);

    return 0;
}
