#include "storage/disk/DiskManager.hpp"

#include "common/Logger.hpp"

#include <cstdlib>
#include <filesystem>

namespace kast {

namespace fs = std::filesystem;

DiskManager::DiskManager() {
  const char *env_path = std::getenv("DATA_PATH");
  data_dir_ = env_path ? fs::path(env_path) : fs::path(".Kast");
  fs::create_directories(data_dir_);
}

ExecutionResult DiskManager::CreateDatabase(std::string_view name) {
  fs::path db_path = data_dir_ / name;
  if (fs::exists(db_path)) {
    return ExecutionResult::Error("Database '" + std::string(name) +
                                  "' already exists.");
  }
  fs::create_directory(db_path);
  LOG_INFO("Created database directory: {}", db_path.string());
  return ExecutionResult::Success(0);
}

} // namespace kast
