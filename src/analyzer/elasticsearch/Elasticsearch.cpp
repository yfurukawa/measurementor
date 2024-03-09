#include "Elasticsearch.h"
#include "TcpClient.h"
#include "TextFileWriter.h"
#include "RestAPIHelper.h"

#include <iostream>

namespace analyzer
{

Elasticsearch::Elasticsearch( std::unique_ptr<::TcpClient> tcpClient, ApiKey apiKey, Version version )
    : tcpClient_( std::move(tcpClient) ),
    apiKey_( apiKey ),
    version_( version )
{
}

void Elasticsearch::registerMeasurementedData(const std::string &registerData)
{
    std::cout << registerData << std::endl;
    std::string method("POST");
    std::string location("/measurementor/_doc/");
    std::string httpVersion("HTTP/1.1");
    std::string hostLocation("Host:localhost:9200");
    std::string userAgent("User-Agent: libnet");
//    std::string key(createBasicAuthorizationKey("apikey:" + apiKey_.get()));
//    std::string authorizationKey("Authorization: Basic " + key);
    std::string acceptInfo("Accept: */*");
    std::string contentType("Content-Type: application/json; charset=UTF-8");
    std::string contentLength("Content-Length: " + std::to_string(registerData.length()) );
    std::string message(method + " " + location + " " + httpVersion + "\r\n" + hostLocation + "\r\n" + userAgent + "\r\n" + acceptInfo + "\r\n" + contentType + "\r\n" + contentLength + "\r\n" + registerData + "\r\n\r\n");
    std::string key(/*createBasicAuthorizationKey("apikey:" + apiKey_.get())*/ "" );

    // TODO 送信文字列のフォーマットをを確認したら有効にする
    // sendRegisterMessage( message );
    
}

void Elasticsearch::sendRegisterMessage( const std::string& registoryString )
{
    // TODO エラー処理を追加
    tcpClient_->openSocket();
    tcpClient_->sendData( registoryString );

    auto response = confirmServerResponse();
    if( response )
    {
        if( response.value() == "Registed" ){
            // Nothing to do
        }
        else{
            // error
        }
    }
    tcpClient_->closeSocket();
}

std::optional<std::string> Elasticsearch::confirmServerResponse()
{
    while( true )
    {
        auto response = tcpClient_->receiveData();
        if( response )
        {
            if( response.value().find("200") ){
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

}
