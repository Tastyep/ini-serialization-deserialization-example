#include "ini.h"

#include "string.h"

#include <exception>
#include <format>
#include <fstream>
#include <string>

namespace ini
{

std::expected<Content, std::string> read(std::istream& input)
{
  Content     content;
  std::string sectionName;

  std::string line;
  while (std::getline(input, line))
  {
    line = trim(line);
    if (line.empty())
    {
      continue;
    }

    if (line.starts_with('[') && line.ends_with(']'))
    {
      sectionName = line.substr(1, line.size() - 2);
      continue;
    }

    if (sectionName.empty())
    {
      return std::unexpected(
          std::format("Missing section name when parsing line '{}'", line));
    }

    const auto sepIdx = line.find_first_of('=');
    if (sepIdx == std::string::npos)
    {
      return std::unexpected(
          std::format("Invalid format '{}', expected 'key = value'", line));
    }

    const auto key            = trim(line.substr(0, sepIdx));
    const auto value          = trim(line.substr(sepIdx + 1));
    content[sectionName][key] = value;
  }

  return content;
}

std::expected<void, std::string> write(const Content& content,
                                       std::ostream&  file)
{
  const auto lastSectionName = std::prev(content.end())->first;
  for (const auto& [sectionName, section] : content)
  {
    file << std::format("[{}]\n", sectionName);
    for (const auto& [key, value] : section)
    {
      file << std::format("{} = {}\n", key, value);
    }

    if (sectionName != lastSectionName)
    {
      file << std::endl;
    }
  }

  return {};
}

} // namespace ini
