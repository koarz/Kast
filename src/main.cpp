#include "common/Kast.hpp"
#include "fmt/color.h"
#include "fmt/core.h"
#include "replxx.hxx"

int main(int argc, char **argv) {
  using namespace replxx;
  kast::Kast kast;
  replxx::Replxx rx;
  rx.install_window_change_handler();

  // 设置高亮回调
  rx.set_highlighter_callback(
      [](std::string const &input, Replxx::colors_t &colors) {
        std::string keyword = ".quit";
        size_t pos = input.find(keyword);
        if (pos != std::string::npos) {
          for (size_t i = 0; i < keyword.size(); ++i) {
            colors.at(pos + i) = Replxx::Color::GREEN;
          }
        }
      });

  fmt::print(fmt::fg(fmt::color::cyan), "  _  __              _   \n"
                                        " | |/ /  __ _   ___| |_ \n"
                                        " | ' /  / _` | / __| __|\n"
                                        " | . \\ | (_| | \\__ \\ |_ \n"
                                        " |_|\\_\\ \\__,_| |___/\\__|\n");
  fmt::print(fmt::fg(fmt::color::gray), " Created by koarz. Version 0.1\n\n");

  while (true) {
    char const *cinput = rx.input("Kast> ");

    std::string input(cinput);
    if (input.empty())
      continue;

    if (input == ".quit") {
      break;
    }

    rx.history_add(input);

    fmt::println("You input: {}", input);
  }
  return 0;
}
