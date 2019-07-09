#ifndef String_HEADER
#define String_HEADER

/**
 * File    : String.h
 * Author  : Kazune Takahashi
 * Created : 7/9/2019, 9:00:03 PM
 * Powered by Visual Studio Code
 */

#include <stdexcept>
#include <cstring>

class String
{
public:
  String();
  String(const char *p);
  String(const String &);            // copy
  String &operator=(const String &); // copy 代入
  String(String &&);                 // move
  String &operator=(String &&);      // move 代入
  ~String()
  {
    if (short_max < sz)
    {
      delete[] ptr;
    }
  }

  char &operator[](int n) { return ptr[n]; }
  char operator[](int n) const { return ptr[n]; }
  char &at(int n)
  {
    check(n);
    return ptr[n];
  }
  char at(int n) const
  {
    check(n);
    return ptr[n];
  }

  String &operator+=(char c);

  char *c_str() { return ptr; }
  const char *c_str() const { return ptr; }

  int size() const { return sz; }
  int capacity() const { return (sz <= short_max) ? short_max : sz + space; }

private:
  static const int short_max = 15;
  int sz;
  char *ptr;
  union {
    int space;
    char ch[short_max + 1];
  };
  void check(int n) const
  {
    if (!(0 <= n && n < sz))
    {
      throw std::out_of_range("String::at()");
    }
  }
  void copy_from(const String &);
  void move_from(String &);
};

char *expand(const char *ptr, int n)
{
  char *p = new char[n];
  std::strcpy(p, ptr);
  return p;
}

#endif // String_HEADER