/*!
 @file Elasticsearch.cpp
 @copyright Copyright 2024 Yoshihiro Furukawa
*/
#include <utility>
#include "Elasticsearch.h"
#include "RestAPIHelper.h"
#include "Index.h"
#include "ITcpClient.h"

namespace analyzer
{

Elasticsearch::Elasticsearch(std::shared_ptr<::ITcpClient> tcpClient, ApiKey apiKey, Version version, std::unique_ptr<Index> index,
                             std::string destination, unsigned int destinationPort)
  : tcpClient_(tcpClient)
  , apiKey_(apiKey)
  , version_(version)
  , index_(std::move(index))
  , destination_(destination)
  , destinationPort_(destinationPort)
  , loggerFactory_(AbstLogger::LoggerFactory::getInstance())
  , logger_(loggerFactory_->createLogger())
{
}

void Elasticsearch::registerMeasurementedData(const std::string& registerData)
{
  std::string method("POST");
  std::string location("/" + index_->get() + "/_doc/");
  std::string httpVersion("HTTP/1.1");
  std::string hostLocation("Host: " + destination_ + ":" + std::to_string(destinationPort_));
  std::string userAgent("User-Agent: libnet");
  //    std::string key(createBasicAuthorizationKey("apikey:" + apiKey_.get()));
  //    std::string authorizationKey("Authorization: Basic " + key);
  std::string acceptInfo("Accept: */*");
  std::string contentType("Content-Type: application/json; charset=UTF-8");
  std::string contentLength("Content-Length: " + std::to_string(registerData.length()));
  std::string message(method + " " + location + " " + httpVersion + "\r\n" + hostLocation + "\r\n" + userAgent + "\r\n" + acceptInfo +
                      "\r\n" + contentType + "\r\n" + contentLength + "\r\n\r\n" + registerData + "\r\n\r\n");

  logger_->log("[elasticsearch] : " + registerData);
  sendRegisterMessage(message);
}

void Elasticsearch::sendRegisterMessage(const std::string& registoryString)
{
  // TODO(yfurukawa) エラー処理を追加
  tcpClient_->openSocket();
  tcpClient_->sendData(registoryString);

  auto response = confirmServerResponse();
  if (response)
  {
    if (response.value() == "Registed")
    {
      // Nothing to do
    }
    else
    {
      // error
    }
  }
  tcpClient_->closeSocket();
}

std::optional<std::string> Elasticsearch::confirmServerResponse()
{
  while (true)
  {
    auto response = tcpClient_->receiveData();
    if (response)
    {
      if (response.value().find("200"))
      {
        // レスポンスコードが200の場合は正常に登録完了
        return "Registed";
      }
      // エラーがないことを確認する
      return "";
    }
    else
    {
      // 受信データが無くなった場合、こっちにくる
      return std::nullopt;
    }
  }
  return "";
}

}  // namespace analyzer
