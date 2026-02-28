#pragma once

#include <string>
namespace kast {
class Kast {

public:
  Kast();

  static bool Execute(std::string sql);
};
} // namespace kast