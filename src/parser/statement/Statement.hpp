#pragma once

#include <memory>

namespace kast {

class Statement;
using StatementPtr = std::shared_ptr<Statement>;

class Statement {
public:
  enum class Type {
    Invalid,
    CreateStatement,
  };

  explicit Statement(Type type) : type_(type) {}
  virtual ~Statement() = default;

  Type GetType() const { return type_; }

private:
  Type type_;
};

} // namespace kast
