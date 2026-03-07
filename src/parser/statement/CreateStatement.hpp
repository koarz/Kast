#pragma once

#include "parser/statement/Statement.hpp"

#include <string>

namespace kast {

class CreateStatement : public Statement {
public:
  enum class CreateType {
    Database,
    Table,
  };

  CreateStatement(CreateType create_type, std::string name)
      : Statement(Type::CreateStatement), create_type_(create_type),
        name_(std::move(name)) {}

  CreateType GetCreateType() const { return create_type_; }
  const std::string &GetName() const { return name_; }

private:
  CreateType create_type_;
  std::string name_;
};

} // namespace kast
