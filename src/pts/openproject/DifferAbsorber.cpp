/*!
 @file      DifferAbsorber.cpp
 @copyright Copyright 2024 Yoshihiro Furukawa
*/
#include "DifferAbsorber.h"

namespace pts
{

std::string DifferAbsorber::convertStatusName(std::string customizedStatusCode, std::string customizedStatusName)
{
  return customizedStatusName;
}

std::string DifferAbsorber::convertStatusCode(std::string customizedStatusCode)
{
  return customizedStatusCode;
}

std::string DifferAbsorber::convertTypeName(std::string customizedTypeCode, std::string customizedTypeName)
{
  return customizedTypeName;
}

std::string DifferAbsorber::convertTypeCode(std::string customizedTypeCode)
{
  return customizedTypeCode;
}

bool DifferAbsorber::isItemData(std::string type)
{
  // 4 represent Feature.
  return type == "4";
}

bool DifferAbsorber::isTaskData(std::string type)
{
  // 1 represent Tassk.
  return type == "1";
}

}  // namespace pts
