#ifndef TRANSFORM_INI_H
#define TRANSFORM_INI_H

#include <expected>
#include <filesystem>
#include <functional>
#include <memory>
#include <string>

class FileFactory;
class Example;

std::expected<void, std::string>
transformExample(const FileFactory&                   fileFactory,
                 const std::filesystem::path&         inputPath,
                 const std::filesystem::path&         outputPath,
                 const std::function<void(Example&)>& transformer);

#endif
