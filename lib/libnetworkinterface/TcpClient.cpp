#include <netdb.h>
#include <netinet/in.h>
#include <sys/fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include "NetworkIfHelper.hpp"
#include "TcpClient.h"

#include <unistd.h>


TcpClient::TcpClient( IPv4 ipAddress, Port port )
    : ip_( ipAddress ),
    port_( port )
{
}

TcpClient::TcpClient( Hostname hostname, Port port )
    : ip_( resolveHostname(hostname) ),
    port_( port )
{
}

TcpClient::~TcpClient() 
{
};

void TcpClient::sendData( std::string content ) const
{
    if( connect(sock_, (struct sockaddr *)&addr_, sizeof(addr_)) > 0 ) {
        perror(("Tcp Client at connect"));
        exit(1);
    }

    if( send( sock_, content.c_str(), content.length(), 0 ) <= 0 ) {
        perror("write");
        exit(1);
    }
}

std::optional<std::string> TcpClient::receiveData()
{
    const int BUFFER_SIZE(10240);
    char receiveBuffer[BUFFER_SIZE] = {0x00};   // テンポラリ受信バッファ ジャンボフレーム対応
    int byteReceived(0);
    int byteIndex(0);

    while (byteIndex < BUFFER_SIZE) {
        byteReceived = recv(sock_, &receiveBuffer[byteIndex], 1, 0);
        if (byteReceived > 0) {
            if (receiveBuffer[byteIndex] == '\n'){
                receiveBuffer[byteIndex+1] = '\0';
                break;
            }
            byteIndex += byteReceived;
        }
        else {
            receiveBuffer[byteIndex] = '\0';
            break;
        }
    }

    if( byteIndex == 0 ) {
        return std::nullopt;
    }
    else {
        std::string s(receiveBuffer);
        return s;
    }
}

void TcpClient::openSocket()
{
    sock_ = socket( PF_INET, SOCK_STREAM, 0 );
    if( sock_ == -1 ) {
        perror("socket");
        exit(1);
    }
    addr_.sin_family = PF_INET;
    addr_.sin_addr.s_addr = inet_addr( ip_.get().c_str() );
    addr_.sin_port = htons( port_.get() );
}

void TcpClient::closeSocket()
{
    close(sock_);
}
