#include "std_lib_facilities.h"  
     void swap_v(int d1, int d2)  
 {  
 int temp = d1;  
 d1 = d2;  
 d2 = temp;  
 }  
   void swap_r(int& d1, int& d2)  
 {  
 int temp = d1;  
 d1 = d2;  
 d2 = temp;  
 }  
   void swap_c(int& d1, int& d2)  
 {  
 int temp = d1;  
 d1 = d2;  
 d2 = temp;  
 }  
  
     int main()  
 {  
 int x = 7;  
 int y = 9;  
 swap_v(x, y);  
 swap_v(7, 9);  
   /*its excutable*/  
     double dx = 7.7;  
 double dy = 9.9;  
 swap_r(dx, dy);  
   const int cx = 7;  
 const int cy = 9;  
 swap_c(cx, cy);  
 
   cout << " x= " << x << " y= " << y << endl;  
 swap(x, y);  
   cout << "x=" << dx << " y=" << dy << endl;  
 swap(x, y);  
   cout << "x=" << cx << " y=" << cy << endl;  
 swap(x, y);  
     return 0;  
   } 
