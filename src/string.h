#ifndef STRING_H
#define STRING_H

#include <algorithm>
#include <cctype>
#include <ranges>
#include <string>
#include <string_view>

[[nodiscard]] constexpr bool isSpace(char q) noexcept {
  static constexpr auto ws = {' ', '\t', '\n', '\v', '\r', '\f'};
  return std::ranges::any_of(ws, [q](auto p) { return p == q; });
};

[[nodiscard]] constexpr std::string trim(std::string_view const in) {
  auto view = in | std::views::drop_while(isSpace) | std::views::reverse |
              std::views::drop_while(isSpace) | std::views::reverse;
  return {view.begin(), view.end()};
}

// std::ranges::to is not yet supported
// constexpr auto trimLeft = std::views::drop_while(isSpace);
// constexpr auto trimRight = std::views::reverse | trimLeft |
// std::views::reverse; constexpr std::string trim(const std::string_view str) {
//   return str | trimLeft | trimRight | std::ranges::to<std::string>();
// }

#endif
