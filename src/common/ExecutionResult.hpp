#pragma once
#include <string>

namespace kast {

// SQL 执行结果
struct ExecutionResult {
  bool success{false};
  std::string error_message{};
  size_t rows_affected{0};

  // 预留位置，未来 SELECT 语句执行完，要把结果集挂在这里
  // ResultSetPtr result_set{nullptr};

  static ExecutionResult Success(size_t rows = 0) { return {true, "", rows}; }

  static ExecutionResult Error(std::string msg) {
    return {false, std::move(msg), 0};
  }
};

} // namespace kast