/*!
 @file      IPv4.h
 @brief     IPv4 address
 @attention
*/
#pragma once

// ---------------< include >----------------------------
#include <string>
#include "NetworkParameter.h"

// --------------< namespace >---------------------------

// ---------< forward declaration >----------------------

/*!
 @class     IPv4
 @brief     IPv4 address
 @attention
*/
class IPv4 final
{
public:
    /*!
     @brief  デフォルトコンストラクタ
    */
    IPv4() = delete;

    /*!
     @brief      コンストラクタ
     @param[in]  ipAddress サーバのIPv4アドレス
    */
    explicit IPv4( std::string ipAddress );

    /*!
     @brief  デフォルトデストラクタ
    */
    virtual ~IPv4() = default;

    /*!
     @brief      IPv4アドレスを得る
     @return     IPv4アドレス
    */
    std::string get();

private:
    IPv4Raw<std::string> ipAddress_;       //!< サーバIPv4アドレス
};
