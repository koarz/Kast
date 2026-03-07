#pragma once

#include "parser/ASTNode.hpp"

#include <expected>

namespace kast {
using ParseResult = std::expected<ASTPtr, std::string>;

class Parser {
  Parser();

  static ParseResult ParseCreateQuery(std::string_view query);

public:
  static ParseResult Parse(std::string_view query);
};
} // namespace kast