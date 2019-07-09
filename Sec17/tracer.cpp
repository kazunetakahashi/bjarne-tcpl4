#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Tracer
{
  string mess;
  Tracer(const string &s) : mess{s}
  {
    clog << mess;
  }
  ~Tracer()
  {
    clog << "~" << mess;
  }
};

void f(const vector<int> &v)
{
  Tracer tr{"in f()\n"};
  for (auto x : v)
  {
    Tracer tr{string{"v loop "} + to_string(x) + '\n'};
  }
}

int main()
{
  f({2, 3, 5});
}