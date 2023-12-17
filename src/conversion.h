#ifndef CONVERTION_H
#define CONVERTION_H

#include "string.h"

#include <array>
#include <boost/core/demangle.hpp>
#include <boost/describe.hpp>
#include <charconv>
#include <concepts>
#include <exception>
#include <expected>
#include <format>
#include <map>
#include <ranges>
#include <string>
#include <string_view>
#include <type_traits>
#include <vector>

namespace bd          = boost::describe;
using ConversionError = std::string;

template<class T>
concept Number =
    (std::integral<T> || std::floating_point<T>)&&!std::same_as<bool, T>;

template<class T>
concept Collection = std::
    same_as<T, std::vector<typename T::value_type, typename T::allocator_type>>;

template<typename T>
std::string typeName()
{
  return boost::core::demangle(typeid(T).name());
}

// Boolean

std::expected<void, ConversionError> convert(std::string_view input, bool& obj)
{
  if (input == "ON")
  {
    obj = true;
  }
  else if (input == "OFF")
  {
    obj = false;
  }
  else
  {
    return std::unexpected(std::format("Cannot convert '{}' to bool", input));
  }

  return {};
}

std::expected<void, ConversionError> convert(bool input, std::string& obj)
{
  obj = input ? "True" : "False";
  return {};
}

// Numbers

std::expected<void, ConversionError> convert(std::string_view input,
                                             Number auto&     obj)
{
  const char* last = input.data() + input.size();
  auto [ptr, ec]   = std::from_chars(input.data(), last, obj);
  if (ec != std::errc())
  {
    return std::unexpected(std::format("Cannot convert '{}' to {}: {}",
                                       input,
                                       typeName<decltype(obj)>(),
                                       std::make_error_code(ec).message()));
  }
  if (ptr != last)
  {
    return std::unexpected(
        std::format("Cannot convert '{}' to {}, '{}' is not a number",
                    input,
                    typeName<decltype(obj)>(),
                    std::string_view(ptr, last)));
  }

  return {};
}

std::expected<void, ConversionError> convert(Number auto  input,
                                             std::string& obj)
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

// Assignable

template<class Input, class Value>
requires std::assignable_from<std::add_lvalue_reference_t<Value>, Input>
std::expected<void, ConversionError> convert(const Input& input, Value& obj)
{
  obj = input;
  return {};
}

// Collections

#include <iostream>

std::expected<void, ConversionError> convert(std::string_view input,
                                             Collection auto& output)
{

  for (const auto value : std::views::split(input, ','))
  {
    output.resize(output.size() + 1);
    const auto& result = convert(trim(std::string_view{value}), output.back());
    if (!result)
    {
      return result;
    }
  }

  return {};
}

std::expected<void, ConversionError> convert(const Collection auto& input,
                                             std::string&           output)
{
  std::string strValue;
  for (const auto& value : input)
  {
    const auto result = convert(value, strValue);
    if (!result)
    {
      return result;
    }

    if (!output.empty())
    {
      output += ", ";
    }
    output += strValue;
  }

  return {};
}

// Described

template<class Value, //
         class Output,
         class Md = bd::describe_members<Output, bd::mod_any_access>>
std::expected<void, ConversionError>
convert(const std::map<std::string, Value>& input, Output& obj)
{
  std::expected<void, ConversionError> result;

  boost::mp11::mp_for_each<Md>(
      [&](auto D)
      {
        if (!result)
        {
          return;
        }
        if (!input.contains(D.name))
        {
          result = std::unexpected(
              std::format("Cannot find a key with the name '{}'", D.name));
          return;
        }
        result = convert(input.at(D.name), obj.*D.pointer);
      });

  return result;
}

template<class Value, //
         class Input,
         class Md = bd::describe_members<Input, bd::mod_any_access>>
std::expected<void, ConversionError>
convert(const Input& input, std::map<std::string, Value>& output)
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

// Create & convert

template<class Output,
         class Md = bd::describe_members<Output, bd::mod_any_access>,
         class Input>
std::expected<Output, ConversionError> convert(const Input& input)
{
  Output output{};

  auto result = convert(input, output);
  if (!result)
  {
    return std::unexpected(result.error());
  }

  return {output};
}

template<class Output,
         class Input,
         class Md = bd::describe_members<Input, bd::mod_any_access>>
std::expected<Output, ConversionError> convert(const Input& input)
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
