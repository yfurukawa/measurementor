#include <netdb.h>
#include <sstream>
#include <string>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include "UdpClient.h"
#include "Hostname.h"
#include "IPv4.h"
#include "NetworkIfHelper.h"
#include "Port.h"

UdpClient::UdpClient( IPv4& ipAddress, Port& port )
{
    this->initialize(ipAddress.get(), port);
}

UdpClient::UdpClient( Hostname& hostname, Port& port )
{
    this->initialize(resolveHostname(hostname), port);
}

void UdpClient::send( std::string content ) const
{
    auto result = sendto( sock_, content.c_str(), content.length(), 0, (struct sockaddr *)&addr_, sizeof(addr_) );
    if( result < 1 ) {
        perror("sendto");
        exit(1);
    }
}

void UdpClient::initialize(std::string ipAddress, Port& port)
{
    sock_ = socket( AF_INET, SOCK_DGRAM, 0 );
    if( sock_ == -1 ) {
        perror("socket");
        exit(1);
    }
    addr_.sin_family = AF_INET;
    addr_.sin_addr.s_addr = inet_addr( ipAddress.c_str() );
    addr_.sin_port = htons( port.get() );
}
