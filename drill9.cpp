#include "std_lib_facilities.h"

struct Date {
    int y;     
    int m;     
    int d;
};

void init_day(Date& dd, int y, int m, int d)
{
    if (d < 1 || d > 31) error("init_day: Invalid day");
    if (m < 1 || m > 12) error("init_day: Invalid month");

    dd.y = y;
    dd.m = m;
    dd.d = d;
}

void add_day(Date& dd, int n)
{
    dd.d += n;
    
    if (dd.d > 31) { ++dd.m; dd.d -= 31; }
    if (dd.d < 1)  { --dd.m; dd.d += 31; }

    if (dd.m > 12) { ++dd.y; dd.m -= 12; }
    if (dd.m < 1)  { --dd.y; dd.m += 12; }
}

ostream& operator<<(ostream& os, const Date& d)
{
    return os << '(' << d.y
              << ',' << d.m
              << ',' << d.d << ')';
}

int main()
try
{
    Date today;
    init_day(today, 1978, 6, 25);

    Date tomorrow{today};
    add_day(tomorrow, 1);

    cout << "Today: " << today << '\n';
    cout << "Tomorrow: " << tomorrow << '\n';

    Date today_e;
    init_day(today_e, 2004, 13, -5);

    return 0;
}
catch(exception& e)
{
    cerr << e.what() << '\n';
    return 1;
}
