#include "file.h"

#include <format>
#include <fstream>

std::expected<std::unique_ptr<std::istream>, std::string>
openInputFile(const std::filesystem::path &path)
{
  auto file = std::make_unique<std::ifstream>(path);
  if (!file->is_open())
  {
    return std::unexpected(
        std::format("Cannot read the file '{}'", path.string()));
  }

  return {std::move(file)};
}

std::expected<std::unique_ptr<std::ostream>, std::string>
openOutputFile(const std::filesystem::path &path)
{
  auto file = std::make_unique<std::ofstream>(path);
  if (!file->is_open())
  {
    return std::unexpected(
        std::format("Cannot write the file '{}'", path.string()));
  }

  return {std::move(file)};
}
