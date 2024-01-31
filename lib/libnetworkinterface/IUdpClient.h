/*!
 @file      IUdpClient.h
 @brief     UDP Client
 @attention
*/
#pragma once

// ---------------< include >----------------------------
#include <string>

// --------------< namespace >---------------------------

// ---------< forward declaration >----------------------
class IPv4;
class Port;
class Hostname;

/*!
 @class     IUdpClient
 @brief     UDP Client
 @attention
*/
class IUdpClient
{
public:
    /*!
    @brief  デフォルトコンストラクタ
    */
    IUdpClient() = default;

    /*!
    @brief      コンストラクタ
    @param[in]  ipAddress サーバアドレス
    @param[in]  port サーバの待ち受けポート番号
    */
    IUdpClient( IPv4& ipAddress, Port& port ){};

    /*!
    @brief      コンストラクタ
    @param[in]  hostname RFC952及びRFC1123に準拠したホスト名
    @param[in]  port サーバの待ち受けポート番号
    */
    IUdpClient( Hostname& hostname, Port& port ){};

    /*!
    @brief  デフォルトデストラクタ
    */
    virtual ~IUdpClient() = default;

    /*!
    @brief      データを送信する
    @param[in]  content 送信データ
    */
    virtual void send( const std::string content ) const = 0;

};
