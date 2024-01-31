#include <exception>
#include <regex>
#include "IPv4.h"

IPv4::IPv4( std::string ipAddress ) : ipAddress_( ipAddress )
{
    std::regex re(R"(^((25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])\.){3}(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])$)");
    if( !std::regex_match( ipAddress_.get(), re) ) {
        std::__throw_invalid_argument("do not match IPv4 format");
    }
}

std::string IPv4::get()
{
    return ipAddress_.get();
}
