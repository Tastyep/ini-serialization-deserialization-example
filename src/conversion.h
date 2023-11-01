#ifndef CONVERTION_H
#define CONVERTION_H

#include <array>
#include <boost/describe.hpp>
#include <charconv>
#include <concepts>
#include <exception>
#include <expected>
#include <format>
#include <map>
#include <string>
#include <string_view>
#include <type_traits>

namespace bd          = boost::describe;
using ConversionError = std::string;

template <typename T>
concept Number = std::integral<T> or std::floating_point<T>;

std::expected<void, ConversionError> convert(std::string_view input,
                                             Number auto     &obj)
{
  const char *last = input.data() + input.size();
  auto [ptr, ec]   = std::from_chars(input.data(), last, obj);
  if (ec != std::errc())
  {
    return std::unexpected(std::format("'{}' cannot be converted: {}",
                                       input,
                                       std::make_error_code(ec).message()));
  }
  if (ec == std::errc::invalid_argument || ptr != last)
  {
    return std::unexpected(std::format("'{}' is not a number", input));
  }

  return {};
}

std::expected<void, ConversionError> convert(Number auto  input,
                                             std::string &obj)
{
  std::array<char, 10> buffer;
  auto [ptr, ec] =
      std::to_chars(buffer.data(), buffer.data() + buffer.size(), input);
  if (ec != std::errc())
  {
    return std::unexpected(std::make_error_code(ec).message());
  }

  obj = std::string_view(buffer.data(), ptr);
  return {};
}

template <class Input, class Value>
  requires std::assignable_from<std::add_lvalue_reference_t<Value>, Input>
std::expected<void, ConversionError> convert(const Input &input, Value &obj)
{
  obj = input;
  return {};
}

template <class Value, //
          class Output,
          class Md = bd::describe_members<Output, bd::mod_any_access>>
std::expected<void, ConversionError>
convert(const std::map<std::string, Value> &input, Output &obj)
{
  std::expected<void, ConversionError> result;

  boost::mp11::mp_for_each<Md>(
      [&](auto D)
      {
        if (!result)
        {
          return;
        }
        result = convert(input.at(D.name), obj.*D.pointer);
      });

  return result;
}

template <class Value, //
          class Input,
          class Md = bd::describe_members<Input, bd::mod_any_access>>
std::expected<void, ConversionError>
convert(const Input &input, std::map<std::string, Value> &output)
{
  std::expected<void, ConversionError> result;

  boost::mp11::mp_for_each<Md>(
      [&](auto D)
      {
        if (!result)
        {
          return;
        }
        result = convert(input.*D.pointer, output[D.name]);
      });

  return result;
}

template <class Output,
          class Md = bd::describe_members<Output, bd::mod_any_access>,
          class Input>
std::expected<Output, ConversionError> convert(const Input &input)
{
  Output output{};

  auto result = convert(input, output);
  if (!result)
  {
    return std::unexpected(result.error());
  }

  return {output};
}

template <class Output,
          class Input,
          class Md = bd::describe_members<Input, bd::mod_any_access>>
std::expected<Output, ConversionError> convert(const Input &input)
{
  Output output{};

  auto result = convert(input, output);
  if (!result)
  {
    return std::unexpected(result.error());
  }

  return {output};
}

#endif
