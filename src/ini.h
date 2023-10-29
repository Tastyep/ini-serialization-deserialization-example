#ifndef INI_H
#define INI_H

#include <expected>
#include <istream>
#include <map>
#include <string>

namespace ini {

using Content = std::map<std::string, std::map<std::string, std::string>>;

std::expected<Content, std::string> read(std::istream &file);
std::expected<void, std::string> write(const Content &content,
                                       std::ostream &file);

} // namespace ini

#endif
