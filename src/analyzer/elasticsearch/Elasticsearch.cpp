#include "Elasticsearch.h"
#include "TcpClient.h"
#include "TextFileWriter.h"
#include "RestAPIHelper.hpp"

#include <iostream>

namespace analyzer
{

Elasticsearch::Elasticsearch( std::unique_ptr<::TcpClient> tcpClient, ApiKey apiKey, Version version )
    : tcpClient_( std::move(tcpClient) ),
    apiKey_( apiKey ),
    version_( version )
{
}

std::string Elasticsearch::sendRegisterMessage(std::string registoryString )
{
    // TODO エラー処理を追加
    tcpClient_->openSocket();
    tcpClient_->sendData( registoryString );
    tcpClient_->closeSocket();

    return "";

}

}
