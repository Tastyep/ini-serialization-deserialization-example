#ifndef INI_H
#define INI_H

#include "file.h"

#include <expected>
#include <map>
#include <string>

namespace ini
{

using Content = std::map<std::string, std::map<std::string, std::string>>;

std::expected<Content, std::string> read(File& file);
void                                write(const Content& content, File& file);

} // namespace ini

#endif
