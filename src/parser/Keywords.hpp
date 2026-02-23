#pragma once

#include <algorithm>
#include <array>
#include <string_view>

namespace kast {
// 使用枚举定义关键字和函数
enum class TokenType {
  // ========
  // KeyWords
  // ========
  KEYWORD_BEGIN,
  CREATE = KEYWORD_BEGIN,
  DATABASE,
  TABLE,
  SELECT,
  QUIT,
  KEYWORD_END,
  // ========
  // Function
  // ========
  FUNC_BEGIN,
  FUNC_SUM = FUNC_BEGIN,
  FUNC_END,
};

// 做字符串和TokenType的映射
struct KeywordEntry {
  std::string_view name;
  TokenType type;
};

// 添加关键字/函数，支持新的关键字/函数只需追加即可
// 自己保证全大写
constexpr auto RAW_KEYWORDS = std::to_array<KeywordEntry>({
    // ---- KeyWords ----
    {"CREATE", TokenType::CREATE},
    {"DATABASE", TokenType::DATABASE},
    {"TABLE", TokenType::TABLE},
    {"SELECT", TokenType::SELECT},
    {"QUIT", TokenType::QUIT},
    // ---- Function ----
    {"SUM", TokenType::FUNC_SUM},
});

// 用位运算将小写字母转为大写，只需清除第六位，也就是 c - 32
// 直接做减法会导致char转为int，所以使用位运算
constexpr char ToUpperFast(char c) {
  return (c >= 'a' && c <= 'z') ? static_cast<char>(c & 0xDF) : c;
}

// 用于作为lower_bound的cmp参数
struct IcaseLess {
  constexpr bool operator()(std::string_view a, std::string_view b) const {
    return std::ranges::lexicographical_compare(a, b, {}, ToUpperFast,
                                                ToUpperFast);
  }
};

// 用于判断两个字符串大小写不敏感情况下是否相等
struct IcaseEqual {
  constexpr bool operator()(std::string_view a, std::string_view b) const {
    return std::ranges::equal(a, b, {}, ToUpperFast, ToUpperFast);
  }
};

// 通过枚举值判断是否为关键字
constexpr bool IsKeyword(TokenType type) {
  return type >= TokenType::KEYWORD_BEGIN && type < TokenType::KEYWORD_END;
}

// 通过枚举值判断是否为函数
constexpr bool IsFunction(TokenType type) {
  return type >= TokenType::FUNC_BEGIN && type < TokenType::FUNC_END;
}

// 编译期排序，将RAW_KEYWORDS按照字典序排序，便于之后的二分查找
consteval auto GetSortedKeywords() {
  auto arr = RAW_KEYWORDS;
  std::ranges::sort(arr, IcaseLess{}, &KeywordEntry::name);
  return arr;
}

class Keywords {
  static constexpr auto SORTED_KEYWORDS = GetSortedKeywords();
  Keywords();

public:
  // 返回word的TokenType
  static std::optional<TokenType> Lookup(std::string_view word) {
    auto it = std::ranges::lower_bound(SORTED_KEYWORDS, word, IcaseLess{},
                                       &KeywordEntry::name);

    if (it != SORTED_KEYWORDS.end() && IcaseEqual{}(it->name, word)) {
      return it->type;
    }
    return std::nullopt;
  }
};
} // namespace kast