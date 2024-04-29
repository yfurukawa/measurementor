/*!
 @file      Dividable.h
 @brief     強く型付けされた変数に除算の能力を付与する
*/
#pragma once

/*!
 @struct    Dividable
 @brief     強く型付けされた変数に除算の能力を付与する
 @tparam    Derived StrongTypeに渡されたテンプレート引数
*/
template< typename Derived >
struct Dividable
{
    /*!
     @brief      左辺を右辺で除算する
     @param[in]  lhs  左辺
     @param[in]  rhs  右辺
    */
    friend Derived& operator/=( Derived& lhs, Derived& rhs ) {
        lhs.get() /= rhs.get();
        return lhs;
    }
    
    /*!
     @brief      左辺を右辺で除算する
     @param[in]  lhs  左辺
     @param[in]  rhs  右辺
    */
    friend Derived operator/( Derived const& lhs, Derived const& rhs ) {
        return Derived{ lhs.get() / rhs.get() };
    }
};

