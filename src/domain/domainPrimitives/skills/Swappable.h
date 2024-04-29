/*!
 @file      Swappable.h
 @brief     強く型付けされた変数に相互入れ替えの能力を付与する
*/
#pragma once

/*!
 @struct    Swappable
 @brief     強く型付けされた変数に相互入れ替えの能力を付与する
 @tparam    Derived StrongTypeに渡されたテンプレート引数
*/
template< typename Derived >
struct Swappable
{
    /*!
     @brief      両辺の値を入れ替える
     @param[in]  lhs  左辺
     @param[in]  rhs  右辺
    */
    friend void swap( Derived& lhs, Derived& rhs )
    {
        using std::swap;
        swap( lhs.get(), rhs.get() );
    }
};
