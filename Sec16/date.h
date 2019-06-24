#ifndef date_HEADER
#define date_HEADER

#include <iostream>

namespace Chrono
{
enum class Month
{
  jan = 1,
  feb,
  mar,
  apr,
  may,
  jun,
  jul,
  aug,
  sep,
  oct,
  nov,
  dec
};

class Date
{
public:
  class Bad_date
  {
  };
  explicit Date(int yy = {}, Month mm = {}, int dd = {});

  // get
  const int year() const { return y; }
  const Month month() const { return m; }
  const int day() const { return d; }

  // add
  Date &add_year(int n);
  Date &add_month(int n);
  Date &add_day(int n);

private:
  bool is_valid();
  int y;
  Month m;
  int d;
};

bool is_date(int y, int m, int d);
bool is_leap_year(int y);
int y_m_days(int y, int m);

bool operator==(const Date &a, const Date &b);
std::ostream &operator<<(std::ostream &os, const Date &a);

const Date &default_date();
extern const int month_days[12];

} // namespace Chrono

#endif // date_HEADER