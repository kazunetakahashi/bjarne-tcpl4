#include "parser.h"
#include "lexer.h"
#include "error.h"
#include "table.h"

using namespace Lexer;
using Table::table;

namespace Driver
{
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
    std::cout << Parser::expr(false) << std::endl;
  }
}
} // namespace Driver

int main()
{
  table["pi"] = 3.14;
  table["e"] = 2.78;
  Driver::calculate();
  return Error::no_of_errors;
}