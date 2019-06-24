#include "date.h"
#include <iostream>

using Chrono::Month;
using Chrono::Date;
using std::cout;
using std::cerr;
using std::endl;

int main()
{
  Date d {2019, Month::jul, 24};
  cout << d << endl;
  d.add_month(20);
  cout << d << endl;
  Date dd {2020, Month::feb, 29};
  cout << dd << " is valid." << endl;
  try
  {
    Date dd {2021, Month::feb, 29};
  }
  catch (Date::Bad_date)
  {
    cerr << "Bad_date tried." << endl;
  }
}