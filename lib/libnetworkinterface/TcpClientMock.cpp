#include "TcpClientMock.h"

TcpClientMock::TcpClientMock()
    : numberOfSent_(0),
    receiveData_("")
{
    sentData_.clear();
}

void TcpClientMock::sendData( std::string content ) const
{
    sentData_.push_back( std::move( content ) );
    ++numberOfSent_;
}

std::optional<std::string> TcpClientMock::receiveData()
{
    return receiveData_;
}

void TcpClientMock::openSocket()
{
    // Nothing to do
}

void TcpClientMock::closeSocket()
{
    // Nothing to do
}
