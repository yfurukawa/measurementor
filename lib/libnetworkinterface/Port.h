/*!
 @file      Port.h
 @brief     TCP/UDP Port
 @attention
*/
#pragma once

// ---------------< include >----------------------------
#include <netinet/in.h>
#include "NetworkParameter.h"

// --------------< namespace >---------------------------

// ---------< forward declaration >----------------------

/*!
 @class     Port
 @brief     TCP/UDP Port
 @attention
*/
class Port final
{
public:
    /*!
    @brief  デフォルトコンストラクタ
    */
    Port() = delete;

    /*!
    @brief      コンストラクタ
    @param[in]  port サーバの待ち受けポート番号
    */
    explicit Port( uint16_t port );

    /*!
    @brief  デフォルトデストラクタ
    */
    virtual ~Port() = default;

    /*!
    @brief      ポート番号を得る
    @return     ポート番号
    */
    uint16_t get();

private:
    PortRaw<uint16_t> port_;       //!< サーバ待ち受けポート
};
