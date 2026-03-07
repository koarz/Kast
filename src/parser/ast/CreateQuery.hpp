#pragma once

#include "parser/ASTNode.hpp"

#include <string_view>

namespace kast {
class CreateQuery : public ASTNode {
public:
  CreateQuery() = default;
  CreateQuery(const CreateQuery &) = default;
  CreateQuery(CreateQuery &&) = default;
  ~CreateQuery() override = default;

  enum class CreateType {
    Database,
    Table,
  };

  CreateQuery(CreateType type, std::string_view name)
      : ASTNode(ASTNode::Type::CreateQuery), type_(type),
        name_(std::move(name)) {}

  CreateType GetType() { return type_; }

  std::string_view GetName() { return name_; }

private:
  CreateType type_;
  std::string_view name_;
};
} // namespace kast