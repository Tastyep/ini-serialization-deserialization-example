#include "stdfile.h"

#include <format>

std::expected<void, std::string>
StdFile::open(const std::filesystem::path& path, OpenMode mode)
{
  std::ios::openmode openMode;
  if (mode == OpenMode::write)
  {
    openMode = std::ios::out;
  }
  else
  {
    openMode = std::ios::in;
  }

  _file = std::make_unique<std::fstream>(path, openMode);
  if (!_file->is_open())
  {
    return std::unexpected(std::format("Cannot open file '{}'", path.string()));
  }

  return {};
}

std::optional<std::string> StdFile::readLine()
{
  std::string line;
  if (!std::getline(*_file, line))
  {
    return {};
  }

  return std::move(line);
}

void StdFile::writeLine(std::string_view line)
{
  *_file << line << std::endl;
}
