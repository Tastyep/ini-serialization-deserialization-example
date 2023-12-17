#include "transformini.h"

#include "conversion.h"
#include "example.h"
#include "file.h"
#include "filefactory.h"
#include "ini.h"

#include <iostream>

std::expected<void, std::string>
transformExample(const FileFactory&                   fileFactory,
                 const std::filesystem::path&         inputPath,
                 const std::filesystem::path&         outputPath,
                 const std::function<void(Example&)>& transformer)
{
  auto inputFile  = fileFactory.makeFile();
  auto outputFile = fileFactory.makeFile();
  if (auto open = inputFile->open(inputPath, File::OpenMode::read); !open)
  {
    return open;
  }

  auto iniContent = ini::read(*inputFile);
  if (!iniContent)
  {
    return std::unexpected(std::move(iniContent.error()));
  }

  auto example = convert<Example>(*iniContent);
  if (!example)
  {
    return std::unexpected(std::move(example.error()));
  }

  transformer(*example);

  auto newIniContent = convert<ini::Content>(*example);
  if (!newIniContent)
  {
    return std::unexpected(std::move(newIniContent.error()));
  }

  if (const auto open = outputFile->open(outputPath, File::OpenMode::write);
      !open)
  {
    return std::unexpected(std::move(open.error()));
  }

  ini::write(*newIniContent, *outputFile);

  return {};
}
