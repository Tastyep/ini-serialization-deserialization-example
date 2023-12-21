#ifndef TRANSFORM_INI_H
#define TRANSFORM_INI_H

#include "conversion.h"
#include "file.h"
#include "filefactory.h"
#include "ini.h"

#include <expected>
#include <filesystem>
#include <functional>
#include <memory>
#include <string>

namespace ini
{
template<class T>
std::expected<void, std::string>
transform(const FileFactory&             fileFactory,
          const std::filesystem::path&   inputPath,
          const std::filesystem::path&   outputPath,
          const std::function<void(T&)>& transformer)
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

  auto obj = convert<T>(*iniContent);
  if (!obj)
  {
    return std::unexpected(std::move(obj.error()));
  }

  transformer(*obj);

  auto newIniContent = convert<ini::Content>(*obj);
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

} // namespace ini

#endif
