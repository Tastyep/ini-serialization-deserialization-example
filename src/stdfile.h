#ifndef STD_FILE_H
#define STD_FILE_H

#include "file.h"

#include <expected>
#include <fstream>
#include <memory>

class StdFile : public File
{
  public:

  std::expected<void, std::string> open(const std::filesystem::path& path,
                                        StdFile::OpenMode mode) override;

  std::optional<std::string> readLine() override;
  void                       writeLine(std::string_view line) override;

  private:

  std::unique_ptr<std::fstream> _file;
  bool                          _eof{false};
};
#endif
