/*!
 @file      Printable.h
 @brief     強く型付けされた変数に標準出力へのデータ出力の能力を付与する
*/
#pragma once

/*!
 @struct    Printable
 @brief     強く型付けされた変数に標準出力へのデータ出力の能力を付与する
 @tparam    Derived StrongTypeに渡されたテンプレート引数
*/
template< typename Derived >
struct Printable
{
    /*!
     @brief      左辺から右辺を減算する
     @param[in]  os   出力先
     @param[in]  d    自分自身
    */
    friend std::ostream& operator<<( std::ostream& os, const Derived& d )
    {
        os << d.get();
        return os;
    }
};
