/*!
 @file      MultipliableWithNumber.h
 @brief     強く型付けされた変数に積算の能力を付与する
*/
#pragma once

/*!
 @struct    MultipliableWithNumber
 @brief     強く型付けされた変数に積算の能力を付与する
 @tparam    Derived StrongTypeに渡されたテンプレート引数
*/
template< typename Derived >
struct MultipliableWithNumber
{
    /*!
     @brief      左辺と右辺を積算する
     @param[in]  lhs  左辺
     @param[in]  rhs  右辺
    */
    friend Derived& operator*=( Derived& lhs, double rhs ) {
        lhs.get() *= rhs;
        return lhs;
    }
    
    /*!
     @brief      左辺と右辺を積算する
     @param[in]  lhs  左辺
     @param[in]  rhs  右辺
    */
    friend Derived operator*( Derived const& lhs, double rhs ) {
        return Derived{ lhs.get() * rhs };
    }
    
    /*!
     @brief      左辺と右辺を積算する
     @param[in]  lhs  左辺
     @param[in]  rhs  右辺
    */
    friend Derived operator*( double lhs, Derived const& rhs ) {
        return Derived{ lhs * rhs.get() };
    }
};
