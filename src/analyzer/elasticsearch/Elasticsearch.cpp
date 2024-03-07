#include "Elasticsearch.h"
#include "TcpClient.h"
#include "TextFileWriter.h"
//#include "RestAPIHelper.hpp"

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

    std::string key(/*createBasicAuthorizationKey("apikey:" + apiKey_.get())*/ "" );
    std::string message("/measurementor/_doc/ HTTP/1.1\r\nHost:localhost:8080\r\nAuthorization: Basic " + key + "\r\n\r\n");

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
