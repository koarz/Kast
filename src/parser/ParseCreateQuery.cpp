#include "parser/Parser.hpp"

#include "clickhouse/parser/TokenIterator.hpp"
#include "parser/Keywords.hpp"
#include "parser/ast/CreateQuery.hpp"

namespace kast {
ParseResult Parser::ParseCreateQuery(std::string_view query) {
  const char *begin = query.data();
  const char *end = begin + query.size();

  DB::Tokens tokens(begin, end);
  DB::TokenIterator it(tokens);

  // 跳过 CREATE
  ++it;

  if (!it.isValid()) {
    return std::unexpected("Expected DATABASE or TABLE after CREATE.");
  }

  auto kw = Keywords::Lookup({it->begin, it->end});
  if (!kw.has_value()) {
    return std::unexpected("Expected DATABASE or TABLE after CREATE, got: " +
                           std::string(it->begin, it->end));
  }

  CreateQuery::CreateType create_type;
  if (*kw == TokenType::DATABASE) {
    create_type = CreateQuery::CreateType::Database;
  } else if (*kw == TokenType::TABLE) {
    create_type = CreateQuery::CreateType::Table;
  } else {
    return std::unexpected("Expected DATABASE or TABLE after CREATE.");
  }

  ++it;

  if (!it.isValid() || it->type == DB::TokenType::Semicolon ||
      it->type == DB::TokenType::EndOfStream) {
    return std::unexpected("Expected a name after CREATE DATABASE/TABLE.");
  }

  std::string_view name(it->begin, it->end);

  return std::make_shared<CreateQuery>(create_type, name);
}
} // namespace kast