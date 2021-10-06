#ifndef DATE_H_INCLUDED
#define DATE_H_INCLUDED




class Date
{
    int mo, da, yr;
public:
    Date() {}
    Date(int d, int m, int y)
    {
        mo = m; da = d; yr = y;
    }
    friend ostream& operator<<(ostream& os, const Date& dt);

    Date operator+(const Date& t) const;
    friend ostream& operator>>(ostream& os, const Date& t);


};

ostream& operator<<(ostream& os, const Date& dt)
{
    os << dt.da << '/' << dt.mo << '/' << dt.yr << endl;
    return os;
}

Date Date::operator+(const Date& t) const
{
    Date sum;
    sum.da = t.da + 3;
    sum.da %= 30;
    sum.mo = t.mo + ((t.da + 3) / 30);
    sum.mo %= 12;
    sum.yr = t.yr + t.mo;

    return sum;
}

ostream& operator>>(ostream& os, const Date& t)
{
    os << t.da << '/' << t.mo << '/' << t.yr<<endl;
    return os;
}
#endif // DATE_H_INCLUDED
