#include "date.h"
#include <iostream>

using Chrono::Month;
using Chrono::Date;
using std::cout;
using std::endl;

int main()
{
  Date d {2019, Month::jul, 24};
  cout << d << endl;
  d.add_month(20);
  cout << d << endl;
}