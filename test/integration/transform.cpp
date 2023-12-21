#include "shared/fakefile.h"
#include "src/example.h"
#include "src/transformini.hpp"
#include "test/integration/filefactorymock.hpp"
#include "trompeloeil.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/trompeloeil.hpp>

SCENARIO("Converting an example structure from an input file to an output file")
{
  FileFactoryMock fileFactory;

  GIVEN("An empty input file")
  {
    auto inputFile  = std::make_shared<FakeFile>();
    auto outputFile = std::make_shared<FakeFile>();

    REQUIRE_CALL(fileFactory, makeFile()).RETURN(outputFile);
    REQUIRE_CALL(fileFactory, makeFile()).RETURN(inputFile);

    WHEN("The data structure is transformed")
    {
      auto result = ini::transform<Example>(
          fileFactory, "input", "output", [](const auto& example) {});

      THEN("It returns a section not found error")
      {
        REQUIRE(!result.has_value());
        REQUIRE(result.error() == "Cannot find a key with the name 'numbers'");
      }
      THEN("The output file is empty")
      {
        REQUIRE(outputFile->content().empty());
      }
    }
  }

  GIVEN("An input file with a valid data structure")
  {
    auto inputFile  = std::make_shared<FakeFile>(R"(
[numbers]
one = 1
two = 2
three = 3.3

[letters]
a = a
b = b
c = c

[bools]
yes = ON
no = OFF

[lists]
intList = 1, 2, 3)");
    auto outputFile = std::make_shared<FakeFile>();

    REQUIRE_CALL(fileFactory, makeFile()).RETURN(outputFile);
    REQUIRE_CALL(fileFactory, makeFile()).RETURN(inputFile);

    WHEN("The data structure is transformed")
    {
      auto result = ini::transform<Example>(
          fileFactory, "input", "output", [](const auto& example) {});

      THEN("The operation succeeds")
      {
        REQUIRE(result.error() == "");
      }
      THEN("Then output matches the input")
      {
        REQUIRE(outputFile->content() ==
                R"([bools]
no = False
yes = True

[letters]
a = a
b = b
c = c

[lists]
intList = 1, 2, 3

[numbers]
one = 1
three = 3.3
two = 2
)");
      }
    }
  }
}
