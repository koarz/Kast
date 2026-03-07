#pragma once

#include "common/ExecutionResult.hpp"
#include "storage/disk/DiskManager.hpp"

#include <string_view>

namespace kast {

class CreateStatement;

class Kast {
  DiskManager disk_manager_;

  ExecutionResult HandleCreateStatement(CreateStatement *stmt);

public:
  Kast();

  ExecutionResult Execute(std::string_view query);
};

} // namespace kast
