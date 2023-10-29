#ifndef CONVERTION_H
#define CONVERTION_H

#include <boost/describe.hpp>
#include <charconv>
#include <concepts>
#include <expected>
#include <format>
#include <map>
#include <string>
#include <string_view>
#include <type_traits>

namespace bd = boost::describe;
using ConversionError = std::string;

std::expected<void, ConversionError> convert(std::string_view input, int &obj) {
  const char *last = input.data() + input.size();
  auto [ptr, ec] = std::from_chars(input.data(), last, obj);
  if (ec == std::errc::invalid_argument || ptr != last) {
    return std::unexpected(std::format("'{}' is not a number", input));
  } else if (ec == std::errc::result_out_of_range) {
    return std::unexpected(std::format("'{}' is larger than an int", input));
  }

  return {};
}

template <class Input, class Value>
  requires std::assignable_from<std::add_lvalue_reference_t<Value>, Input>
std::expected<void, ConversionError> convert(const Input &input, Value &obj) {
  obj = input;
  return {};
}

template <class Value, //
          class T, class Md = bd::describe_members<T, bd::mod_any_access>>
std::expected<void, ConversionError>
convert(const std::map<std::string, Value> &input, T &obj) {
  std::expected<void, ConversionError> result;

  boost::mp11::mp_for_each<Md>([&](auto D) {
    if (!result) {
      return;
    }
    result = convert(input.at(D.name), obj.*D.pointer);
  });

  return result;
}

template <class T, class Bd = bd::describe_bases<T, bd::mod_any_access>,
          class Md = bd::describe_members<T, bd::mod_any_access>, class Input>
std::expected<T, ConversionError> convert(const Input &input) {
  T obj{};

  auto result = convert(input, obj);
  if (!result) {
    return std::unexpected(result.error());
  }

  return {obj};
}

#endif
