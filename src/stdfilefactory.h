#ifndef STD_FILE_FACTORY_H
#define STD_FILE_FACTORY_H

#include "filefactory.h"

#include <memory>

class StdFileFactory : public FileFactory
{
  public:

  std::shared_ptr<File> makeFile() const override;
};

#endif
