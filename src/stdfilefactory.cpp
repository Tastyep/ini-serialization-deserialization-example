#include "stdfilefactory.h"

#include "stdfile.h"

std::shared_ptr<File> StdFileFactory::makeFile() const
{
  return std::make_shared<StdFile>();
}
