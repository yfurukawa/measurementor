#include "DifferAbsorber.h"

namespace pts
{

std::string DifferAbsorber::convertStatusName(std::string customizedStatusCode, std::string customizedStatusName)
{
  int customizedCode(std::stoi(customizedStatusCode));
  std::string convertedNane("");
  
  switch(customizedCode)
  {
    case 15:
      convertedNane = "New";
      break;
    case 16:
      convertedNane = "InProgress";
      break;
    case 17:
      convertedNane = "Review";
      break;
    case 18:
      convertedNane = "Close";
    break;
    case 19:
      convertedNane = "Close";
      break;
    default:
      convertedNane = customizedStatusName;
      break;
  }
  return convertedNane;
}

std::string DifferAbsorber::convertStatusCode(std::string customizedStatusCode)
{
  int customizedCode(std::stoi(customizedStatusCode));
  std::string convertedCode("");

  switch(customizedCode)
  {
    case 15:  // New
      convertedCode = "1";
      break;
    case 16:  // In Progress
      convertedCode = "7";
      break;
    case 17:  // Review
      convertedCode = "15";
      break;
    case 18:  // Close
      convertedCode = "12";
      break;
    case 19:  // Also Close
      convertedCode = "12";
      break;
    default:  // It Is not need to convert
      convertedCode = customizedStatusCode;
      break;
  }
  return convertedCode;
}

std::string DifferAbsorber::convertTypeName(std::string customizedTypeCode, std::string customizedTypeName)
{
  int customizedCode(std::stoi(customizedTypeCode));
  std::string convertedName("");
  
  switch(customizedCode)
  {
    case 8:  // Task
      convertedName = "Task";
      break;
    case 9:
      convertedName = "Item";
      break;
    default:
      convertedName = customizedTypeName;
      break;
  }
  return convertedName;
}

std::string DifferAbsorber::convertTypeCode(std::string customizedTypeCode)
{
  int customizedCode(std::stoi(customizedTypeCode));
  std::string convertedCode("");
  
  switch(customizedCode)
  {
    case 8:
      convertedCode = "1";
      break;
    case 9:
      convertedCode = "4";
      break;
    default:
      convertedCode = customizedTypeCode;
      break;
  }
  return convertedCode;
}

bool DifferAbsorber::isItemData(std::string type)
{
  // 4 represent Feature that is default value.
  // 9 represent Feature that is customized value.
  return (type == "9") || (type == "4");
}

bool DifferAbsorber::isTaskData(std::string type)
{
  // 1 represent Task that is default value.
  // 8 represent Task that is customized value.
  return (type == "8") || (type == "1");
}

}  // namespace pts
