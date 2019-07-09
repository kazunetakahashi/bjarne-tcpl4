/**
 * File    : String.cpp
 * Author  : Kazune Takahashi
 * Created : 7/9/2019, 9:08:41 PM
 * Powered by Visual Studio Code
 */

#include "String.h"
#include <iostream>
using std::istream;
using std::ostream;

void String::copy_from(const String &x)
{
  if (x.sz <= short_max)
  {
    std::memcpy(this, &x, sizeof(x));
    ptr = ch;
  }
  else
  {
    ptr = expand(x.ptr, x.sz + 1);
    sz = x.sz;
    space = 0;
  }
}

void String::move_from(String &x)
{
  if (x.sz <= short_max)
  {
    std::memcpy(this, &x, sizeof(x));
    ptr = ch;
  }
  else
  {
    ptr = x.ptr;
    sz = x.sz;
    space = x.space;
    x.ptr = x.ch;
    x.sz = 0;
    x.ch[0] = 0;
  }
}

String::String() : sz{0}, ptr{ch}
{
  ch[0] = 0;
}

String::String(const char *p) : sz(std::strlen(p)), ptr{(sz <= short_max) ? ch : new char[sz + 1]}, space{0}
{
  std::strcpy(ptr, p);
}

String::String(const String &x)
{
  copy_from(x);
}

String::String(String &&x)
{
  move_from(x);
}

String &String::operator=(const String &x)
{
  if (this == &x)
  {
    return *this;
  }
  if (short_max < sz)
  {
    delete[] ptr;
  }
  copy_from(x);
  return *this;
}

String &String::operator=(String &&x)
{
  if (this == &x)
  {
    return *this;
  }
  if (short_max < sz)
  {
    delete[] ptr;
  }
  move_from(x);
  return *this;
}

String &String::operator+=(char c)
{
  if (sz == short_max)
  {
    int n = sz * 2 + 2;
    ptr = expand(ptr, n);
    space = n - sz - 2;
  }
  else if (short_max < sz)
  {
    if (space == 0)
    {
      int n = sz * 2 + 2;
      char *p = expand(ptr, n);
      delete ptr;
      ptr = p;
      space = n - sz - 2;
    }
    else
    {
      --space;
    }
  }
  ptr[sz] = c;
  ptr[++sz] = 0;
  return *this;
}

ostream &operator<<(ostream &os, const String &s)
{
  return os << s.c_str();
}

istream &operator>>(istream &is, String &s)
{
  s = "";
  is >> std::ws;
  char ch{};
  while (is.get(ch) && !std::isspace(ch))
  {
    s += ch;
  }
  return is;
}

bool operator==(const String &a, const String &b)
{
  if (a.size() != b.size())
  {
    return false;
  }
  for (auto i = 0; i < a.size(); i++)
  {
    if (a[i] != b[i])
    {
      return false;
    }
  }
  return true;
}

bool operator!=(const String &a, const String &b)
{
  return !(a == b);
}

bool operator<(const String &a, const String &b)
{
  for (auto i = 0; i <= a.size(); i++)
  {
    if (a[i] < b[i])
    {
      return true;
    }
    else if (a[i] > b[i])
    {
      return false;
    }
  }
  return false;
}

bool operator<=(const String &a, const String &b)
{
  return a < b || a == b;
}

bool operator>(const String &a, const String &b)
{
  return !(a <= b);
}

bool operator>=(const String &a, const String &b)
{
  return a > b || a == b;
}

char *begin(String &x)
{
  return x.c_str();
}

char *end(String &x)
{
  return x.c_str() + x.size();
}

const char *begin(const String &x)
{
  return x.c_str();
}

const char *end(const String &x)
{
  return x.c_str() + x.size();
}

String &operator+=(String &a, const String &b)
{
  for (auto x : b)
  {
    a += x;
  }
  return a;
}

String operator+(const String &a, const String &b)
{
  String ans{a};
  ans += b;
  return ans;
}