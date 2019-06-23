#ifndef lexer_HEADER
#define lexer_HEADER

#include <string>
#include <iostream>

using std::istream;
using std::string;

namespace Lexer
{
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
class Token
{
public:
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
    {
      delete ip;
    }
  }
  istream *ip;
  bool owns;
  Token ct{Kind::end};
};
extern Token_stream ts;
} // namespace Lexer

#endif // lexer_HEADER