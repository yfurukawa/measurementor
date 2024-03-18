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

        /*!
    @brief      同じ型の変数同士で等価（＝）演算を行う
    @return     true : 左辺と右辺が等価
    */
    friend bool operator==( IPv4& lhs, IPv4& rhs ) {
        return lhs.get() == rhs.get();
    }

    /*!
    @brief      数値との間で等価（＝）演算を行う
    @return     true : 左辺と右辺が等価
    */
    friend bool operator==( IPv4& lhs, std::string const& factor ) {
        return lhs.get() == factor;
    }

    /*!
    @brief      同じ型の変数同士で不等価（＜）演算を行う
    @return     true : 左辺と右辺が不等価
    */
    friend bool operator!=( IPv4& lhs, IPv4& rhs ) {
        return lhs.get() != rhs.get();
    }

    /*!
    @brief      数値との間で不等価（＜）演算を行う
    @return     true : 左辺と右辺が不等価
    */
    friend bool operator!=( IPv4& lhs, std::string const& factor ) {
        return lhs.get() != factor;
    }

private:
    IPv4Raw<std::string> ipAddress_;       //!< サーバIPv4アドレス
};
