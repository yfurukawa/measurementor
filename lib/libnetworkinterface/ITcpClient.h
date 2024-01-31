/*!
 @file      ITcpClient.h
 @brief     TCP Clientのインターフェース
 @attention
*/
#pragma once

// ---------------< include >----------------------------
#include <optional>
#include <string>

// --------------< namespace >---------------------------

// ---------< forward declaration >----------------------
class IPv4;
class Port;
class Hostname;

/*!
 @class     ITcpClient
 @brief     TCP Clientのインターフェース
 @attention
*/
class ITcpClient
{
public:
    /*!
    @brief  デフォルトコンストラクタ
    */
    ITcpClient() = default;

    /*!
    @brief      コンストラクタ
    @param[in]  ipAddress サーバアドレス
    @param[in]  port サーバの待ち受けポート番号
    */
    ITcpClient( IPv4& ipAddress, Port& port ){};

    /*!
    @brief      コンストラクタ
    @param[in]  hostname RFC952及びRFC1123に準拠したホスト名
    @param[in]  port サーバの待ち受けポート番号
    */
    ITcpClient( Hostname& hostname, Port& port ){};

    /*!
    @brief  デフォルトデストラクタ
    */
    virtual ~ITcpClient() = default;

    /*!
    @brief      データを送信する
    @param[in]  content 送信データ
    */
    virtual void sendData( const std::string content ) const = 0;

    /*!
    @brief   データを受信する
    @return  受信データ。受信データが無い場合は無効値を返す
    */
    virtual std::optional<std::string> receiveData() = 0;
};
