#include "common/Kast.hpp"

#include "common/Logger.hpp"
#include "parser/Parser.hpp"
#include "parser/binder/Binder.hpp"
#include "parser/statement/CreateStatement.hpp"
#include "parser/statement/Statement.hpp"

namespace kast {

Kast::Kast() {
  Logger::Init();
  LOG_INFO("Kast started!");
}

ExecutionResult Kast::HandleCreateStatement(CreateStatement *stmt) {
  switch (stmt->GetCreateType()) {
  case CreateStatement::CreateType::Database:
    return disk_manager_.CreateDatabase(stmt->GetName());
  case CreateStatement::CreateType::Table:
    return ExecutionResult::Error("CREATE TABLE is not supported yet.");
  }
  return ExecutionResult::Error("Unknown CREATE type.");
}

ExecutionResult Kast::Execute(std::string_view query) {
  auto parse_result = Parser::Parse(query);
  if (!parse_result.has_value()) {
    return ExecutionResult::Error(parse_result.error());
  }

  auto bind_result = Binder::Bind(parse_result.value());
  if (!bind_result.has_value()) {
    return ExecutionResult::Error(bind_result.error());
  }

  StatementPtr stmt = bind_result.value();

  switch (stmt->GetType()) {
  case Statement::Type::CreateStatement:
    return HandleCreateStatement(static_cast<CreateStatement *>(stmt.get()));
  default: return ExecutionResult::Error("Unsupported SQL operation.");
  }
}

} // namespace kast
