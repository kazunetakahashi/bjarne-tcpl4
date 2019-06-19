#include <iostream>
#include <string>
#include <map>
#include <cctype>
using namespace std;

enum class Kind : char
{
  name,
  number,
  end,
  plus = '+',
  minus = '-',
  mul = '*',
  div = '/',
  print = ';',
  assign = '=',
  lp = '(',
  rp = ')',
};

struct Token
{
  Kind kind;
  string string_value;
  double number_value;
};

class Token_stream
{
public:
  Token_stream(istream &s) : ip{&s}, owns{false} {};
  Token_stream(istream *p) : ip{p}, owns{true} {};

  ~Token_stream() { close(); }

  Token get();
  const Token &current() { return ct; }

  void set_input(istream &s)
  {
    close();
    ip = &s;
    owns = false;
  }

  void set_input(istream *p)
  {
    close();
    ip = p;
    owns = true;
  }

private:
  void close()
  {
    if (owns)
      delete ip;
  }
  istream *ip;
  bool owns;
  Token ct{Kind::end};
};

int no_of_errors;
Token_stream ts{cin};
map<string, double> table;

double error(const string &s)
{
  no_of_errors++;
  cerr << "error: " << s << endl;
  return 1;
}

double expr(bool);

double prim(bool get)
{
  if (get)
  {
    ts.get();
  }
  switch (ts.current().kind)
  {
  case Kind::number:
  {
    double v = ts.current().number_value;
    ts.get();
    return v;
  }
  case Kind::name:
  {
    double &v = table[ts.current().string_value];
    if (ts.get().kind == Kind::assign)
    {
      v = expr(true);
    }
    return v;
  }
  case Kind::minus:
    return -prim(true);
  case Kind::lp:
  {
    auto e = expr(true);
    if (ts.current().kind != Kind::rp)
    {
      return error("')' expected");
    }
    ts.get();
    return e;
  }
  default:
    return error("primary expected");
  }
}

double term(bool get)
{
  double left = prim(get);
  while (true)
  {
    switch (ts.current().kind)
    {
    case Kind::mul:
      left *= prim(true);
      break;
    case Kind::div:
      if (auto d = prim(true))
      {
        left /= d;
        break;
      }
    default:
      return left;
    }
  }
}

double expr(bool get)
{
  double left = term(get);
  while (true)
  {
    switch (ts.current().kind)
    {
    case Kind::plus:
      left += term(true);
      break;
    case Kind::minus:
      left -= term(true);
      break;
    default:
      return left;
    }
  }
}

Token Token_stream::get()
{
  char ch = 0;

  // *ip >> ch;
  do
  {
    if (!ip->get(ch))
    {
      return ct = {Kind::end};
    }
  } while (ch != '\n' && isspace(ch));

  switch (ch)
  {
  case ';':
  case '\n':
    return ct = {Kind::print};
  case '*':
  case '/':
  case '+':
  case '-':
  case '(':
  case ')':
  case '=':
    return ct = {static_cast<Kind>(ch)};
  case '0':
  case '1':
  case '2':
  case '3':
  case '4':
  case '5':
  case '6':
  case '7':
  case '8':
  case '9':
  case '.':
    ip->putback(ch);
    *ip >> ct.number_value;
    ct.kind = Kind::number;
    return ct;
  default:
    if (isalpha(ch))
    {
      /*
      ip->putback(ch);
      *ip >> ct.string_value;
      ct.kind = Kind::name;
      return ct;
      */
      ct.string_value = ch;
      while (ip->get(ch))
      {
        if (isalnum(ch))
        {
          ct.string_value += ch;
        }
        else
        {
          ip->putback(ch);
          break;
        }
      }
      ct.kind = Kind::name;
      return ct;
    }
    error("bad token");
    return ct = {Kind::print};
  }
}

void calculate()
{
  while (true)
  {
    ts.get();
    if (ts.current().kind == Kind::end)
    {
      break;
    }
    if (ts.current().kind == Kind::print)
    {
      continue;
    }
    cout << expr(false) << endl;
  }
}

int main()
{
  table["pi"] = 3.14;
  table["e"] = 2.78;
  calculate();
  return no_of_errors;
}