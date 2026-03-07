#pragma once

#include "common/ExecutionResult.hpp"

#include <filesystem>
#include <string_view>

namespace kast {

class DiskManager {
  std::filesystem::path data_dir_;

public:
  DiskManager();

  ExecutionResult CreateDatabase(std::string_view name);
};

} // namespace kast
