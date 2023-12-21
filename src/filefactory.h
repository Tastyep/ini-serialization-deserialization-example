#ifndef FILE_FACTORY_H
#define FILE_FACTORY_H

#include <memory>

class File;

class FileFactory
{
  public:

  virtual ~FileFactory()                         = default;
  virtual std::shared_ptr<File> makeFile() const = 0;
};

#endif
