#include "clickhouse/parser/Lexer.hpp"
#include "common/Kast.hpp"
#include "fmt/base.h"
#include "fmt/color.h"
#include "fmt/core.h"
#include "parser/Keywords.hpp"
#include "replxx.hxx"

#include <chrono>

int main(int argc, char **argv) {
  using namespace replxx;
  kast::Kast db;
  replxx::Replxx rx;
  rx.install_window_change_handler();

  // 设置高亮回调
  rx.set_highlighter_callback(
      [](std::string const &input, replxx::Replxx::colors_t &colors) {
        if (input.empty())
          return;
        const char *begin = input.data();
        const char *end = begin + input.size();

        // 直接使用ClickHouse的分词器来分Token
        DB::Lexer lexer(begin, end);

        while (true) {
          DB::Token token = lexer.nextToken();

          if (token.type == DB::TokenType::EndOfStream) {
            break;
          }

          replxx::Replxx::Color color = replxx::Replxx::Color::DEFAULT;

          auto token_type = kast::Keywords::Lookup({token.begin, token.end});

          if (token_type.has_value()) {
            if (kast::IsFunction(*token_type)) {
              color = replxx::Replxx::Color::MAGENTA;
            } else if (kast::IsKeyword(*token_type)) {
              color = replxx::Replxx::Color::CYAN;
            }

            if (color != replxx::Replxx::Color::DEFAULT) {
              size_t start_idx = token.begin - begin;
              size_t end_idx = token.end - begin;

              // 越界防御
              if (end_idx <= colors.size()) {
                for (size_t i = start_idx; i < end_idx; ++i) {
                  colors[i] = color;
                }
              }
            }
          }
        }
      });

  fmt::print(fmt::fg(fmt::color::cyan), "  _  __              _   \n"
                                        " | |/ /  __ _   ___| |_ \n"
                                        " | ' /  / _` | / __| __|\n"
                                        " | . \\ | (_| | \\__ \\ |_ \n"
                                        " |_|\\_\\ \\__,_| |___/\\__|\n");
  fmt::print(fmt::fg(fmt::color::gray), " Created by koarz. Version 0.1\n\n");
  [&]() { // 这里使用lambda表达式方便快速退出嵌套循环
    while (true) {
      std::string query;
      bool first_line = true;

      while (true) {
        char const *cinput =
            first_line ? rx.input("Kast> ") : rx.input("... > ");
        if (cinput == nullptr) {
          return;
        }
        std::string input(cinput);
        if (input == "quit;") {
          return;
        }
        if (input.empty() || input.starts_with("//"))
          continue;
        rx.history_add(input);

        if (!query.empty())
          query += ' ';
        query += input;

        if (!query.empty())
          query += ' ';
        query += input;

        if (input.ends_with(';')) {
          break;
        }
        first_line = false;
      }
      const auto start = std::chrono::steady_clock::now();
      if (auto result = db.Execute(query); !result.success) {
        fmt::println("{}", result.error_message);
      }
      const auto end = std::chrono::steady_clock::now();

      const std::chrono::duration<double> diff = end - start;
      fmt::println("\nTime : {:.5f}s\n", diff.count());
    }
  }();
  fmt::println("Bye.");
  return 0;
}
