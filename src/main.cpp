#include "example.h"
#include "stdfilefactory.h"
#include "transformini.h"

#include <iostream>
#include <memory>

int main(void)
{
  const auto result = transformExample(//
      StdFileFactory{},
      std::filesystem::path{"../asset/example.ini"},
      std::filesystem::path{"../output/example.ini"},
      [](Example& example)
      {
        example.numbers.two = 9;
        example.letters.c   = "z";
        example.lists.intList.push_back(4);
      });
  if (!result)
  {
    std::cerr << result.error() << std::endl;
    return 1;
  }

  return 0;
}
