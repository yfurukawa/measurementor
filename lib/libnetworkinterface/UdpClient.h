/*!
 @file      UdpClient.h
 @brief     UDP Client
 @attention
*/
#pragma once

// ---------------< include >----------------------------
#include <memory>
#include <string>
#include <arpa/inet.h>
#include "IUdpClient.h"

// --------------< namespace >---------------------------

// ---------< forward declaration >----------------------

/*!
 @class     UdpClient
 @brief     UDP Client
 @attention
*/
class UdpClient final : public IUdpClient
{
public:
    /*!
    @brief  デフォルトコンストラクタ
    */
    UdpClient() = delete;

    /*!
    @brief      コンストラクタ
    @param[in]  ipAddress サーバアドレス
    @param[in]  port サーバの待ち受けポート番号
    */
    UdpClient( IPv4& ipAddress, Port& port );

    /*!
    @brief      コンストラクタ
    @param[in]  hostname RFC952及びRFC1123に準拠したホスト名
    @param[in]  port サーバの待ち受けポート番号
    */
    UdpClient( Hostname& hostname, Port& port );

    /*!
    @brief  デフォルトデストラクタ
    */
    virtual ~UdpClient() = default;

    /*!
    @brief      データを送信する
    @param[in]  content 送信データ
    */
    void send( const std::string content ) const override;

private:
    int sock_;                            //!< 送信用ソケット
    struct sockaddr_in addr_;             //!< ネットワーク設定

    void initialize(std::string ipAddress, Port& port);
};
