#include "parser/Parser.hpp"

#include "clickhouse/parser/TokenIterator.hpp"
#include "parser/Keywords.hpp"

namespace kast {
ParseResult Parser::Parse(std::string_view input) {
  const char *begin = input.data();
  const char *end = begin + input.size();

  DB::Tokens tokens(begin, end);
  DB::TokenIterator it(tokens);

  if (!it.isValid()) {
    return std::unexpected("Empty query.");
  }

  auto kw = Keywords::Lookup({it->begin, it->end});
  if (!kw.has_value()) {
    return std::unexpected("Unknown keyword: " +
                           std::string(it->begin, it->end));
  }

  switch (*kw) {
  case TokenType::CREATE:
    return ParseCreateQuery(input);
  default:
    return std::unexpected("Unsupported statement.");
  }
}
} // namespace kast