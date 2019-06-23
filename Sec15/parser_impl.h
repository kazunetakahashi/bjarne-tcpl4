#ifndef parser_impl_HEADER
#define parser_impl_HEADER

#include "parser.h"
#include "error.h"
#include "lexer.h"

using Error::error;
using namespace Lexer;

namespace Parser
{
double prim(bool get);
double term(bool get);
double expr(bool get);
} // namespace Parser

#endif // parser_impl_HEADER