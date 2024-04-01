/*!
 @file      Repository.cpp
 @copyright Copyright 2024 Yoshihiro Furukawa
*/
#include <string>
#include "ITcpClient.h"
#include "Repository.h"
#include "TextFileWriter.h"

namespace repository
{

  void Repository::registerInProgressStartDate(measurementor::TaskId taskId, measurementor::UpdatedAt updateAt)
  {

  }

  measurementor::UpdatedAt Repository::getInProgressStartedDate(measurementor::TaskId taskId)
  {
    auto ud = measurementor::UpdatedAt{"2024-04-01T12:34:56Z"};
    return ud;
  }

}  // repository