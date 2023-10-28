#include "ini.h"
#include <iostream>

int main(void) {
  const auto iniContent =
      ini::read(std::filesystem::path{"../asset/example.ini"});
  if (!iniContent) {
    std::cerr << iniContent.error() << std::endl;
    return 1;
  }

  return 0;
}
