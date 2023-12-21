#ifndef FILE_FACTORY_MOCK_H
#define FILE_FACTORY_MOCK_H

#include "src/filefactory.h"
#include "trompeloeil.hpp"

class FileFactoryMock : public trompeloeil::mock_interface<FileFactory>
{
  IMPLEMENT_CONST_MOCK0(makeFile);
};

#endif
