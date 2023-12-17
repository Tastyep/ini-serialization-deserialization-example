#include "stdfilefactory.h"

#include "stdfile.h"

std::unique_ptr<File> StdFileFactory::makeFile() const
{
  return std::make_unique<StdFile>();
}
