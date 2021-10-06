#ifndef TIME_H_INCLUDED
#define TIME_H_INCLUDED
#pragma once


class Date
{
    int mo, da, yr;
public:
    Date() {}
    Date(int d, int m, int y)
    {
        mo = m; da = d; yr = y;
    }
    void date();
    void date2();
};


void Date::date() {
    SYSTEMTIME st;
    GetSystemTime(&st);
    yr = st.wYear;
    mo = st.wMonth;
    da =  st.wDayOfWeek;
    cout << yr << '-' << mo << '-' << da << ' ';

}

void Date::date2() {

    SYSTEMTIME st;
    GetSystemTime(&st);
    yr = st.wYear;
    mo = st.wMonth;
    da =  st.wDayOfWeek+3;
    cout << yr << '-' << mo << '-' << da << ' ';
}




#endif // TIME_H_INCLUDED
