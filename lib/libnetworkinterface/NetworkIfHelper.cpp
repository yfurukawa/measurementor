#include <netdb.h>
#include <sstream>
#include <string>
#include "NetworkIfHelper.h"
#include "Hostname.h"
#include "clx/base64.h"

/*!
 @fn         resolveHostname
 @brief      ホスト名の名前解決をしてIPアドレスを得る
 @param[in]  hostname RFC952及びRFC1123に準拠したホスト名
 @return     IPアドレス（v4）
*/
std::string resolveHostname(Hostname& hostname)
{
    auto host = gethostbyname( hostname.get().c_str() );
    std::stringstream ss;

    ss << std::to_string( (unsigned char)*(host->h_addr_list[0]) ) << "."
    << std::to_string( (unsigned char)*(host->h_addr_list[0] + 1) ) << "."
    << std::to_string( (unsigned char)*(host->h_addr_list[0] + 2) ) << "."
    << std::to_string( (unsigned char)*(host->h_addr_list[0] + 3) );

    return ss.str();
}
