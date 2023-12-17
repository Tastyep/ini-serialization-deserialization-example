#include "fakefile.h"

#include <utility>

FakeFile::FakeFile(std::string content) : _stream(std::move(content)) {}

std::expected<void, std::string>
FakeFile::open([[maybe_unused]] const std::filesystem::path& path,
               [[maybe_unused]] OpenMode                     mode)
{
  return {};
}

std::optional<std::string> FakeFile::readLine()
{
  std::string line;
  if (!std::getline(_stream, line))
  {
    return {};
  }

  return std::move(line);
}

void FakeFile::writeLine(std::string_view line)
{
  _stream << line << '\n';
}
