#ifndef FILE_H
#define FILE_H

#include <expected>
#include <filesystem>
#include <istream>
#include <memory>
#include <ostream>
#include <string>

std::expected<std::unique_ptr<std::istream>, std::string>
openInputFile(const std::filesystem::path &path);

std::expected<std::unique_ptr<std::ostream>, std::string>
openOutputFile(const std::filesystem::path &path);

#endif
