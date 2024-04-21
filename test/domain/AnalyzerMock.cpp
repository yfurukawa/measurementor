/*!
 @file AnalyzerMock.cpp
 @copyright Copyright 2024 Yoshihiro Furukawa
*/
#include <utility>
#include "AnalyzerMock.h"
#include "../../src/analyzer/elasticsearch/Index.h"
#include "ITcpClient.h"

namespace analyzer
{

void AnalyzerMock::registerMeasurementedData(const std::string& indexSuffix, const std::string& registerData)
{
}

void AnalyzerMock::sendRegisterMessage(const std::string& registoryString)
{
}

std::optional<std::string> AnalyzerMock::confirmServerResponse()
{
  return "";
}

}  // namespace analyzer
