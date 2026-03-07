#pragma once

#include "parser/ASTNode.hpp"
#include "parser/statement/Statement.hpp"

#include <expected>
#include <string>

namespace kast {

using BindResult = std::expected<StatementPtr, std::string>;

class Binder {
public:
  static BindResult Bind(ASTPtr ast);
};

} // namespace kast
