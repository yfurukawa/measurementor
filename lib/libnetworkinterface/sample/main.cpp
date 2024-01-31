#include <iostream>
#include <memory>
#include <string>
#include <optional>
#include "INetworkClient.h"
#include "TcpClient.h"
#include "Hostname.h"
#include "Port.h"
#include "IPv4.h"

int main()
{
    Port p(80);
    IPv4 ip("192.168.1.1");
    Hostname host("localhost");
    std::string received("");
    std::optional<std::string> result;

    auto client = std::make_unique<TcpClient>(ip,p);
    client->sendData("GET /\n");
    while(true) {
        result = client->receiveData();
        if( result ) {
            received += result.value();
        }
        else {
            break;
        }
    }

    std::cout << received << std::endl;

  return 0;
}

