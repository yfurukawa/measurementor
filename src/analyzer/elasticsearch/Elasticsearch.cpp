#include "Elasticsearch.h"
#include "TcpClient.h"
#include "TextFileWriter.h"
#include "RestAPIHelper.hpp"

#include <iostream>

namespace analyzer
{

Elasticsearch::Elasticsearch( std::unique_ptr<::TcpClient> tcpClient, ApiKey apiKey )
    : tcpClient_( std::move(tcpClient) ),
    apiKey_( apiKey )
{
}

std::string Elasticsearch::sendQueryMessage( std::string queryMessage )
{
    // TODO エラー処理を追加
    tcpClient_->openSocket();
    tcpClient_->sendData( queryMessage );
    tcpClient_->closeSocket();

    return "";

}

}
