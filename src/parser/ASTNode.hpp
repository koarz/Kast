#pragma once

#include <memory>
#include <vector>

namespace kast {
class ASTNode;

using ASTPtr = std::shared_ptr<ASTNode>;

class ASTNode {
public:
  enum class Type {
    InValid,
    CreateQuery,
  };

  Type node_type_ = Type::InValid;

public:
  std::vector<ASTPtr> children_;

  virtual ~ASTNode() = default;
  ASTNode() = default;
  ASTNode(const ASTNode &) = default;
  ASTNode &operator=(const ASTNode &) = default;

  ASTNode(Type node_type) : node_type_(node_type) {}
  Type GetNodeType() { return node_type_; }
};

} // namespace kast