#include "src/ini.h"

#include "shared/fakefile.h"

#include <catch2/catch_test_macros.hpp>
#include <sstream>

using namespace std::literals;

SCENARIO("Reading content from a correctly formatted input stream")
{
  GIVEN("An input stream with correctly formatted content")
  {
    auto input = FakeFile(R"(
[Section1]
key1 = value1
key2 = value2

[Section2]
key3 = value3
)");
    WHEN("read is called")
    {
      auto result = ini::read(input);
      THEN("it returns a valid Content structure")
      {
        REQUIRE(result.has_value());
        auto content = result.value();
        REQUIRE(content["Section1"]["key1"] == "value1");
        REQUIRE(content["Section1"]["key2"] == "value2");
        REQUIRE(content["Section2"]["key3"] == "value3");
      }
    }
  }
}

SCENARIO("Reading content from an empty input stream")
{
  GIVEN("An empty input stream")
  {
    auto input = FakeFile("");
    WHEN("read is called")
    {
      auto result = ini::read(input);
      THEN("it returns a valid but empty Content structure")
      {
        REQUIRE(result.has_value());
        REQUIRE(result.value().empty());
      }
    }
  }
}

SCENARIO("Reading content from an input stream missing a section name")
{
  GIVEN("An input stream with a key-value pair but missing section name")
  {
    auto input = FakeFile("key1 = value1");
    WHEN("read is called")
    {
      auto result = ini::read(input);
      THEN("it returns an error")
      {
        REQUIRE(result.error() ==
                "Missing section name when parsing line 'key1 = value1'");
      }
    }
  }
}

SCENARIO("Reading content from an input stream with invalid format")
{
  GIVEN("An input stream with a line missing the '=' character")
  {
    auto input = FakeFile(R"(
[Section1]
key1 value1
)");
    WHEN("read is called")
    {
      auto result = ini::read(input);
      THEN("it returns an error")
      {
        REQUIRE(result.error() ==
                "Invalid format 'key1 value1', expected 'key = value'");
      }
    }
  }
}

SCENARIO("Reading content with extra whitespaces")
{
  GIVEN("An input stream with extra whitespaces around keys and values")
  {
    auto input = FakeFile(R"(
[Section1]
key1   =   value1   
)");
    WHEN("read is called")
    {
      auto result = ini::read(input);
      THEN("it correctly trims these whitespaces")
      {
        REQUIRE(result.has_value());
        auto content = result.value();
        REQUIRE(content["Section1"]["key1"] == "value1");
      }
    }
  }

  GIVEN("An input stream with extra whitespaces around the section name")
  {
    auto input = FakeFile(R"(
  [Section1]  
key1 = value1   
)");
    WHEN("read is called")
    {
      auto result = ini::read(input);
      THEN("it correctly trims these whitespaces")
      {
        REQUIRE(result.has_value());
        auto content = result.value();
        REQUIRE(content["Section1"]["key1"] == "value1");
      }
    }
  }
}

SCENARIO("Reading content with empty lines")
{
  GIVEN("An input stream with empty lines")
  {
    auto input = FakeFile(R"(

[Section1]

key1 = value1

)");
    WHEN("read is called")
    {
      auto result = ini::read(input);
      THEN("it ignores these lines and parses the rest correctly")
      {
        REQUIRE(result.has_value());
        auto content = result.value();
        REQUIRE(content["Section1"]["key1"] == "value1");
      }
    }
  }
}
