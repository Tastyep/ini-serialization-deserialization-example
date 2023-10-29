#include "convertion.h"
#include "example.h"
#include "ini.h"
#include <iostream>

int main(void) {
  const auto iniContent =
      ini::read(std::filesystem::path{"../asset/example.ini"});
  if (!iniContent) {
    std::cerr << iniContent.error() << std::endl;
    return 1;
  }

  auto example = convert<Example>(*iniContent);
  if (!example) {
    std::cerr << example.error() << std::endl;
    return 1;
  }

  example->numbers.two = 9;
  example->letters.c = "z";

  const auto newIniContent = convert<ini::Content>(*example);

  const auto wrote = ini::write(*newIniContent,
                                std::filesystem::path{"../output/example.ini"});
  if (!wrote) {
    std::cerr << wrote.error() << std::endl;
    return 1;
  }

  return 0;
}
