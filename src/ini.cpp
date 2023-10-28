#include "ini.h"

#include "string.h"
#include <exception>
#include <format>
#include <fstream>
#include <iostream>
#include <string>
namespace ini {

std::expected<Content, std::string> read(const std::filesystem::path &path) {
  std::ifstream file{path};
  if (!file.is_open()) {
    return std::unexpected(
        std::format("Cannot read the file '{}'", path.string()));
  }

  Content content;
  std::string sectionName;

  std::string line;
  while (std::getline(file, line)) {
    if (line.empty()) {
      continue;
    }

    if (line.starts_with('[') && line.ends_with(']')) {
      sectionName = line.substr(1, line.size() - 2);
      continue;
    }

    if (sectionName.empty()) {
      return std::unexpected(
          std::format("Missing section name when parsing line '{}'", line));
    }

    const auto sepIdx = line.find_first_of('=');
    if (sepIdx == std::string::npos) {
      return std::unexpected(
          std::format("Invalid format '{}', expected 'key = value'", line));
    }

    const auto key = trim(line.substr(0, sepIdx));
    const auto value = trim(line.substr(sepIdx + 1));
    content[sectionName][key] = value;
    std::cout << key << " " << value << std::endl;
  }

  return content;
}

std::expected<void, std::string> write(const Content &content,
                                       std::filesystem::path &path) {
  return {};
}

} // namespace ini
