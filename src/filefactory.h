#ifndef FILE_FACTORY_H
#define FILE_FACTORY_H

#include "file.h"

#include <memory>

class FileFactory
{
  public:

  virtual std::unique_ptr<File> makeFile() const = 0;
};

#endif
