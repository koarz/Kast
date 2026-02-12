#include "common/Kast.hpp"
#include "common/Logger.hpp"

namespace kast {
Kast::Kast() {
  Logger::Init();
  LOG_INFO("Kast started!");
}
} // namespace kast