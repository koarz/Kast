#include "parser/binder/Binder.hpp"

#include "parser/ast/CreateQuery.hpp"
#include "parser/statement/CreateStatement.hpp"

namespace kast {

BindResult Binder::Bind(ASTPtr ast) {
  if (!ast) {
    return std::unexpected("Null AST node.");
  }

  switch (ast->GetNodeType()) {
  case ASTNode::Type::CreateQuery: {
    auto *node = static_cast<CreateQuery *>(ast.get());
    if (node->GetName().empty()) {
      return std::unexpected("Name cannot be empty.");
    }
    CreateStatement::CreateType type =
        node->GetType() == CreateQuery::CreateType::Database
            ? CreateStatement::CreateType::Database
            : CreateStatement::CreateType::Table;
    return std::make_shared<CreateStatement>(type, std::string(node->GetName()));
  }
  default:
    return std::unexpected("Unsupported statement type.");
  }
}

} // namespace kast
