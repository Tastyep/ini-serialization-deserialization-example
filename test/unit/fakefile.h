#ifndef FAKE_FILE_H
#define FAKE_FILE_H

#include "src/file.h"

#include <sstream>
#include <string>

class FakeFile : public File
{
  public:

  explicit FakeFile(std::string content);

  std::expected<void, std::string> open(const std::filesystem::path& path,
                                        OpenMode mode) override;

  std::optional<std::string> readLine() override;
  void                       writeLine(std::string_view line) override;

  private:

  std::stringstream _stream;
};

#endif
