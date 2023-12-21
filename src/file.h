#ifndef FILE_H_
#define FILE_H_

#include <expected>
#include <filesystem>
#include <optional>
#include <string>
#include <string_view>

class File
{
  public:

  enum class OpenMode
  {
    read  = 1 << 0,
    write = 1 << 1,
  };

  public:

  virtual ~File() = default;
  virtual std::expected<void, std::string>
  open(const std::filesystem::path& path, OpenMode mode) = 0;

  virtual std::optional<std::string> readLine()                       = 0;
  virtual void                       writeLine(std::string_view line) = 0;
};

#endif // !FILE_H_
