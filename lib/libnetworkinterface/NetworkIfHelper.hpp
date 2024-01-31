/*!
 @file      INetworkClient.h
 @brief     Network Clientのインターフェース
 @attention
*/
#pragma once

// ---------------< include >----------------------------
#include <netdb.h>
#include <sstream>
#include <string>
#include "Hostname.h"

/*!
 @fn resolveHostname
 @brief      コンストラクタ
 @param[in]  hostname RFC952及びRFC1123に準拠したホスト名
 @param[in]  port サーバの待ち受けポート番号
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
