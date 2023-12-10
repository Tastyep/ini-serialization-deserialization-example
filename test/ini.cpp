#include <catch2/catch_test_macros.hpp>

#include <sstream>
#include "ini.h"

SCENARIO("Reading an ini content from a stream", "[ini]") {
  GIVEN("A person represented as one section and two attributes") {
    std::stringstream file;

    file << "[Person]\n";
    file << "name = Bob\n";
    file << "age = 40\n";

    WHEN("The content is parsed") {
      auto result = ini::read(file);

      THEN("The Person data structure is correctly parsed") {
        REQUIRE(result.has_value());
        REQUIRE(result.value().contains("Person"));
        REQUIRE(result.value()["Person"]["name"] == "Bob");
        REQUIRE(result.value()["Person"]["age"] == "40");
      }
    }
  }
}
