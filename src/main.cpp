#include "conversion.h"
#include "example.h"
#include "file.h"
#include "ini.h"

#include <iostream>

int main(void)
{
  auto iniFile = openInputFile(std::filesystem::path{"../asset/example.ini"});
  if (!iniFile)
  {
    std::cerr << iniFile.error() << std::endl;
    return 1;
  }

  const auto iniContent = ini::read(**iniFile);
  if (!iniContent)
  {
    std::cerr << iniContent.error() << std::endl;
    return 1;
  }

  auto example = convert<Example>(*iniContent);
  if (!example)
  {
    std::cerr << example.error() << std::endl;
    return 1;
  }

  example->numbers.two = 9;
  example->letters.c   = "z";
  example->lists.intList.push_back(4);

  const auto newIniContent = convert<ini::Content>(*example);

  auto outputFile =
      openOutputFile(std::filesystem::path{"../output/example.ini"});
  if (!outputFile)
  {
    std::cerr << outputFile.error() << std::endl;
    return 1;
  }

  const auto wrote = ini::write(*newIniContent, **outputFile);
  if (!wrote)
  {
    std::cerr << wrote.error() << std::endl;
    return 1;
  }

  return 0;
}
