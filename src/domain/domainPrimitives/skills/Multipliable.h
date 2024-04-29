/*!
 @file      Multipliable.h
 @brief     強く型付けされた変数に積算の能力を付与する
*/
#pragma once

/*!
 @struct    Multipliable
 @brief     強く型付けされた変数に積算の能力を付与する
 @tparam    Derived StrongTypeに渡されたテンプレート引数
*/
template< typename Derived >
struct Multipliable
{
    /*!
     @brief      左辺と右辺を積算する
     @param[in]  lhs  左辺
     @param[in]  rhs  右辺
    */
    friend Derived& operator*=( Derived& lhs, Derived& rhs ) {
        lhs.get() *= rhs.get();
        return lhs;
    }
    
    /*!
     @brief      左辺と右辺を積算する
     @param[in]  lhs  左辺
     @param[in]  rhs  右辺
    */
    friend Derived operator*( Derived const& lhs, Derived const& rhs ) {
        return Derived{ lhs.get() * rhs.get() };
    }

};
