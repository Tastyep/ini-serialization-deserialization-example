#include "ini.h"

#include "string.h"

#include <exception>
#include <format>
#include <fstream>
#include <string>

namespace ini
{

std::expected<Content, std::string> read(File& input)
{
  Content     content;
  std::string sectionName;

  for (std::optional<std::string> readLine; (readLine = input.readLine());)
  {
    auto line = trim(*readLine);
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

void write(const Content& content, File& file)
{
  const auto lastSectionName = std::prev(content.end())->first;
  for (const auto& [sectionName, section] : content)
  {
    file.writeLine(std::format("[{}]", sectionName));
    for (const auto& [key, value] : section)
    {
      file.writeLine(std::format("{} = {}", key, value));
    }

    if (sectionName != lastSectionName)
    {
      file.writeLine("");
    }
  }
}

} // namespace ini
