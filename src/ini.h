#ifndef INI_H
#define INI_H

#include <expected>
#include <filesystem>
#include <map>
#include <string>

namespace ini {

using Content = std::map<std::string, std::map<std::string, std::string>>;

std::expected<Content, std::string> read(const std::filesystem::path &path);
std::expected<void, std::string> write(const Content &content,
                                       std::filesystem::path &path);

} // namespace ini

#endif
