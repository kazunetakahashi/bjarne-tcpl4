/**
 * File    : main.cpp
 * Author  : Kazune Takahashi
 * Created : 7/18/2019, 9:03:14 PM
 * Powered by Visual Studio Code
 */

// 4-Tuple の実装

#include <iostream>
#include <algorithm>
#include <memory>
#include <numeric>
using std::istream;
using std::ostream;

class Nil // 実際は使わない。特殊化の際に「下の方」を使わせるためのもの。
{
};

template <int I, typename T1 = Nil, typename T2 = Nil, typename T3 = Nil, typename T4 = Nil>
struct select_base;

template <int I, typename T1 = Nil, typename T2 = Nil, typename T3 = Nil, typename T4 = Nil>
using Select = typename select_base<I, T1, T2, T3, T4>::type;

template <typename T1, typename T2, typename T3, typename T4>
struct select_base<0, T1, T2, T3, T4>
{
  using type = T1;
};

template <typename T1, typename T2, typename T3, typename T4>
struct select_base<1, T1, T2, T3, T4>
{
  using type = T2;
};

template <typename T1, typename T2, typename T3, typename T4>
struct select_base<2, T1, T2, T3, T4>
{
  using type = T3;
};

template <typename T1, typename T2, typename T3, typename T4>
struct select_base<3, T1, T2, T3, T4>
{
  using type = T4;
};

template <typename T1 = Nil, typename T2 = Nil, typename T3 = Nil, typename T4 = Nil>
struct Tuple : Tuple<T2, T3, T4>
{
  T1 x;
  using Base = Tuple<T2, T3, T4>;
  Base *base() { return static_cast<Base *>(this); }
  const Base *base() const { return static_cast<const Base *>(this); }

  Tuple(const T1 &t1, const T2 &t2, const T3 &t3, const T4 &t4) : Base{t2, t3, t4}, x{t1} {}
  Tuple() {}

  bool operator<(const Tuple &t) const
  {
    if (x == t.x)
    {
      return (*base() < *t.base());
    }
    return x < t.x;
  }
};

template <>
struct Tuple<>
{
  Tuple() {}

  bool operator<(const Tuple &t) const
  {
    return false;
  }
};

template <typename T1>
struct Tuple<T1> : Tuple<>
{
  T1 x;
  using Base = Tuple<>;
  Base *base() { return static_cast<Base *>(this); }
  const Base *base() const { return static_cast<const Base *>(this); }

  Tuple(const T1 &t1) : Base{}, x{t1} {}
  Tuple() {}

  bool operator<(const Tuple &t) const
  {
    return x < t.x;
  }
};

template <typename T1, typename T2>
struct Tuple<T1, T2> : Tuple<T2>
{
  T1 x;
  using Base = Tuple<T2>;
  Base *base() { return static_cast<Base *>(this); }
  const Base *base() const { return static_cast<const Base *>(this); }

  Tuple(const T1 &t1, const T2 &t2) : Base{t2}, x{t1} {}
  Tuple() {}

  bool operator<(const Tuple &t) const
  {
    if (x == t.x)
    {
      return (*base() < *t.base());
    }
    return x < t.x;
  }
};

template <typename T1, typename T2, typename T3>
struct Tuple<T1, T2, T3> : Tuple<T2, T3>
{
  T1 x;
  using Base = Tuple<T2, T3>;
  Base *base() { return static_cast<Base *>(this); }
  const Base *base() const { return static_cast<const Base *>(this); }

  Tuple(const T1 &t1, const T2 &t2, const T3 &t3) : Base{t2, t3}, x{t1} {}
  Tuple() {}

  bool operator<(const Tuple &t) const
  {
    if (x == t.x)
    {
      return (*base() < *t.base());
    }
    return x < t.x;
  }
};

template <typename T1, typename T2, typename T3, typename T4>
void print_elements(ostream &os, const Tuple<T1, T2, T3, T4> &t)
{
  os << t.x << ", ";
  print_elements(os, *t.base());
}

template <typename T1, typename T2, typename T3>
void print_elements(ostream &os, const Tuple<T1, T2, T3> &t)
{
  os << t.x << ", ";
  print_elements(os, *t.base());
}

template <typename T1, typename T2>
void print_elements(ostream &os, const Tuple<T1, T2> &t)
{
  os << t.x << ", ";
  print_elements(os, *t.base());
}

template <typename T1>
void print_elements(ostream &os, const Tuple<T1> &t)
{
  os << t.x;
}

template <>
void print_elements(ostream &os, const Tuple<> &t)
{
  os << " ";
}

template <typename T1, typename T2, typename T3, typename T4>
ostream &operator<<(ostream &os, const Tuple<T1, T2, T3, T4> &t)
{
  os << "{ ";
  print_elements(os, t);
  return os << " }";
}

template <typename Ret, int N>
struct getNth
{
  template <typename T>
  static Ret &get(T &t)
  {
    return getNth<Ret, N - 1>::get(*t.base());
  }
};

template <typename Ret>
struct getNth<Ret, 0>
{
  template <typename T>
  static Ret &get(T &t) { return t.x; }
};

template <int N, typename T1, typename T2, typename T3, typename T4>
Select<N, T1, T2, T3, T4> &get(Tuple<T1, T2, T3, T4> &t)
{
  return getNth<Select<N, T1, T2, T3, T4>, N>::get(t);
}

template <typename T1, typename T2, typename T3, typename T4>
Tuple<T1, T2, T3, T4> make_tuple(const T1 &t1, const T2 &t2, const T3 &t3, const T4 &t4)
{
  return Tuple<T1, T2, T3, T4>{t1, t2, t3, t4};
}

template <typename T1, typename T2, typename T3>
Tuple<T1, T2, T3> make_tuple(const T1 &t1, const T2 &t2, const T3 &t3)
{
  return Tuple<T1, T2, T3>{t1, t2, t3};
}

template <typename T1, typename T2>
Tuple<T1, T2> make_tuple(const T1 &t1, const T2 &t2)
{
  return Tuple<T1, T2>{t1, t2};
}

template <typename T1>
Tuple<T1> make_tuple(const T1 &t1)
{
  return Tuple<T1>{t1};
}

#include <stdexcept>
#include <cstring>

class String
{
public:
  String();
  String(const char *p);
  String(const String &);            // copy
  String &operator=(const String &); // copy ä»£å…¥
  String(String &&);                 // move
  String &operator=(String &&);      // move ä»£å…¥
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

// https://github.com/kazunetakahashi/bjarne-ppp2/blob/master/Sec19/main.cpp

namespace My_vector
{
template <typename T, typename A>
struct vector_base
{
  A alloc;
  T *elem;
  unsigned long sz;
  unsigned long space;
  vector_base(const A &a, unsigned long n = 0) : alloc{a}, elem{alloc.allocate(n)}, sz{n}, space{n} {}
  vector_base(const vector_base &) = delete;
  vector_base &operator=(const vector_base &) = delete;
  vector_base(vector_base &&);
  vector_base &operator=(vector_base &&);
  ~vector_base()
  {
    alloc.deallocate(elem, space);
  }
};

template <typename T, typename A>
vector_base<T, A>::vector_base(vector_base &&b) : alloc{b.alloc}, elem{b.elem}, sz{b.sz}, space{b.space}
{
  b.elem = nullptr;
  b.sz = b.space = 0;
}

template <typename T, typename A>
vector_base<T, A> &vector_base<T, A>::operator=(vector_base &&b)
{
  swap(*this, b);
  return *this;
}

template <typename T, typename A>
void swap(vector_base<T, A> &x, vector_base<T, A> &y)
{
  vector_base<T, A> tmp{x.alloc, 0};
  tmp.elem = x.elem;
  tmp.sz = x.sz;
  tmp.space = x.space;
  x.alloc = y.alloc;
  x.elem = y.elem;
  x.sz = y.sz;
  x.space = y.space;
  y.alloc = tmp.alloc;
  y.elem = tmp.elem;
  y.sz = y.sz;
  y.space = y.space;
  tmp.elem = nullptr;
  tmp.sz = tmp.space = 0;
}

template <typename T, typename A = std::allocator<T>>
class vector : private vector_base<T, A>
{
public:
  using size_type = unsigned long;
  using value_type = T;
  using iterator = T *;
  using const_iterator = T *;

  vector() : vector_base<T, A>{A{}} {}
  explicit vector(size_type);
  ~vector() {}
  vector(const vector &);
  vector &operator=(const vector &);
  vector(vector &&);
  vector &operator=(vector &&);

  T &operator[](size_type n) { return this->elem[n]; }
  const T &operator[](size_type n) const { return this->elem[n]; }
  T &at(size_type n);

  iterator begin() { return this->elem; };
  const_iterator begin() const { return this->elem; };
  iterator end() { return this->elem + size(); };
  const_iterator end() const { return this->elem + size(); };

  size_type size() const { return this->sz; }
  size_type capacity() const { return this->space; }

  void resize(size_type, T val = T());
  void push_back(const T &);
  void reserve(size_type);
};

template <typename T, typename A>
vector<T, A>::vector(size_type s) : vector_base<T, A>{A{}, s}
{
  std::uninitialized_fill(this->elem, this->elem + size(), T{});
}

template <typename T, typename A>
vector<T, A>::vector(const vector &v)
    : vector<T, A>(v.size())
{
  std::uninitialized_copy(v->elem, v->elem + v.size(), this->elem);
}

template <typename T, typename A>
vector<T, A> &vector<T, A>::operator=(const vector &v)
{
  vector tmp{v};
  swap(*this, tmp);
  return *this;
}

template <typename T, typename A>
vector<T, A>::vector(vector &&v)
{
  swap(*this, v);
}

template <typename T, typename A>
vector<T, A> &vector<T, A>::operator=(vector &&v)
{
  swap(*this, v);
  return *this;
}

template <typename T, typename A>
T &vector<T, A>::at(size_type n)
{
  if (!(0 <= n && n < size()))
  {
    throw std::out_of_range("bad index.");
  }
  return this->elem[n];
}

template <typename T, typename A>
void vector<T, A>::resize(size_type newsize, T val)
{
  reserve(newsize);
  if (size() < newsize)
  {
    std::uninitialized_fill(this->elem + size(), this->elem + newsize, val);
  }
  else
  {
    for (auto i = newsize; i < size(); i++)
    {
      this->alloc.destory(this->elem + i);
    }
  }
  this->space = this->elem + newsize;
}

template <typename T, typename A>
void vector<T, A>::push_back(const T &val)
{
  if (this->space == 0)
  {
    reserve(8);
  }
  else if (size() == this->space)
  {
    reserve(2 * size());
  }
  this->alloc.construct(this->elem + size(), val);
  this->sz++;
}

template <typename T, typename A>
void vector<T, A>::reserve(size_type newalloc)
{
  if (newalloc <= this->space)
  {
    return;
  }
  vector_base<T, A> b(this->alloc, newalloc);
  b.sz = size();
  std::uninitialized_copy(this->elem, this->elem + size(), b.elem);
  for (auto i = 0; i < size(); i++)
  {
    this->alloc.destroy(this->elem + i);
  }
  swap(*this, b);
}
} // namespace My_vector

using restaurant = Tuple<String, int, unsigned int>;

int main()
{
  unsigned int N;
  std::cin >> N;
  My_vector::vector<restaurant> V{N};
  for (auto i = 0u; i < N; i++)
  {
    String S;
    int P;
    std::cin >> S >> P;
    V[i] = make_tuple(S, -P, i + 1);
  }
  std::sort(V.begin(), V.end());
  for (auto i = 0u; i < N; i++)
  {
    std::cout << get<2>(V[i]) << std::endl;
  }
}