#include "date.h"
#include <memory>

using Chrono::Date;
using Chrono::Month;

const Date &Chrono::default_date()
{
  static Date d {1970, Month::jan, 1};
  return d;
}

const int Chrono::month_days[12] = {
  31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

Date::Date(int yy, Month mm, int dd) : y{yy}, m{mm}, d{dd}
{
  if (y == 0)
  {
    y = default_date().year();
  }
  if (m == Month{})
  {
    m = default_date().month();
  }
  if (d == 0)
  {
    d = default_date().day();
  }
  if (!is_valid())
  {
    throw Bad_date();
  }
}

bool Date::is_valid()
{
  return Chrono::is_date(y, static_cast<int>(m), d);
}

bool Chrono::is_date(int y, int m, int d)
{
  if (!(1 <= y && 1 <= m && m <= 12))
  {
    return false;
  }
  int D = Chrono::y_m_days(y, m);
  return (1 <= d && d <= D);
}

int Chrono::y_m_days(int y, int m)
{
  int D = Chrono::month_days[m - 1];
  if (Chrono::is_leap_year(y) && m == 2)
  {
    ++D;
  }
  return D;
}

bool Chrono::is_leap_year(int y)
{
  if (y % 400 == 0)
  {
    return true;
  }
  else if (y % 100 == 0)
  {
    return false;
  }
  else
  {
    return (y % 4 == 0);
  }
}

bool Chrono::operator==(const Date &a, const Date &b)
{
  return (a.year() == b.year() && a.month() == b.month() && a.day() == b.day());
}

std::ostream &Chrono::operator<<(std::ostream &os, const Date &a)
{
  return os << a.year() << "-" << static_cast<int>(a.month()) << "-" << a.day();
}

Date& Date::add_year(int n)
{
  y += n;
  if (!is_valid())
  {
    throw Bad_date();
  }
  return *this;
}

Date& Date::add_month(int n)
{
  if (!(n >= 0))
  {
    throw Bad_date();
  }
  int mon_cnt = static_cast<int>(month()) - 1;
  mon_cnt += n;
  y += mon_cnt / 12;
  m = static_cast<Month>(mon_cnt % 12 + 1);
  if (!is_valid())
  {
    throw Bad_date();
  }
  return *this;
}

Date& Date::add_day(int n)
{
  if (!(n >= 0))
  {
    throw Bad_date();
  }
  // 書くのめんどいので略。
  return *this;
}