/*!
 @file      Subtractable.h
 @brief     強く型付けされた変数に減算の能力を付与する
*/
#pragma once

/*!
 @struct    Subtractable
 @brief     強く型付けされた変数に減算の能力を付与する
 @tparam    Derived StrongTypeに渡されたテンプレート引数
*/
template< typename Derived >
struct Subtractable
{
    /*!
     @brief      左辺から右辺を減算する
     @param[in]  lhs  左辺
     @param[in]  rhs  右辺
    */
    friend Derived& operator-=( Derived& lhs, Derived& rhs ) {
        lhs.get() -= rhs.get();
        return lhs;
    }
    
    /*!
     @brief      左辺から右辺を減算する
     @param[in]  lhs  左辺
     @param[in]  rhs  右辺
    */
    friend Derived operator-( Derived const& lhs, Derived const& rhs ) {
        return Derived{ lhs.get() - rhs.get() };
    }
};
