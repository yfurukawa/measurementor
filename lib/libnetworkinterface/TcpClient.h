/*!
 @file      TcpClient.h
 @brief     Tcp Client
 @attention
*/
#pragma once

// ---------------< include >----------------------------
#include <memory>
#include <arpa/inet.h>
#include "ITcpClient.h"

// --------------< namespace >---------------------------

// ---------< forward declaration >----------------------

/*!
 @class     TcpClient
 @brief     TcpClient
 @attention
*/
class TcpClient final : public ITcpClient
{
public:
    /*!
    @brief  デフォルトコンストラクタ
    */
    TcpClient() = delete;

    /*!
    @brief      コンストラクタ
    @param[in]  ipAddress サーバアドレス
    @param[in]  port サーバの待ち受けポート番号
    */
    TcpClient( IPv4& ipAddress, Port& port );

    /*!
    @brief      コンストラクタ
    @param[in]  hostname RFC952及びRFC1123に準拠したホスト名
    @param[in]  port サーバの待ち受けポート番号
    */
    TcpClient( Hostname& hostname, Port& port );

    /*!
    @brief  デフォルトデストラクタ
    */
    virtual ~TcpClient();

    /*!
    @brief      データを送信する
    @param[in]  content 送信データ
    */
    void sendData( const std::string content ) const override;

    /*!
    @brief   データを受信する
    @return  受信データ。受信データが無い場合は無効値を返す
    */
    std::optional<std::string> receiveData() override;

private:
    int sock_;                            //!< 送信用ソケット
    struct sockaddr_in addr_;             //!< ネットワーク設定

    void initialize(std::string ipAddress, Port& port);
};
