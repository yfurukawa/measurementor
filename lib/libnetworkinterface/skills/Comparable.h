/*!
 @file      Comparable.h
 @brief     強く型付けされた変数に比較演算の能力を付与する
*/
#pragma once

/*!
 @struct    Comparable
 @brief     強く型付けされた変数に比較演算の能力を付与する
 @tparam    Derived StrongTypeに渡されたテンプレート引数
*/
template< typename Derived >
struct Comparable
{
    /*!
    @brief      同じ型の変数同士で小なり（＜）比較を行う
    @return     true : 左辺が右辺より小さい
    */
    friend bool operator<( Derived const& lhs, Derived const& rhs ) {
        return lhs.get() < rhs.get();
    }

    /*!
    @brief      数値との間でで小なり（＜）比較を行う
    @return     true : 比較値より小さい
    */
    friend bool operator<( Derived const& lhs, double const& factor ) {
        return lhs.get() < factor;
    }

    /*!
    @brief      同じ型の変数同士で大なり（＞）比較を行う
    @return     true : 左辺が右辺より大きい
    */
        friend bool operator>( Derived const& lhs, Derived const& rhs ) {
        return lhs.get() > rhs.get();
    }

    /*!
    @brief      数値との間で大なり（＞）比較を行う
    @return     true : 左辺が右辺より大きい
    */
    friend bool operator>( Derived const& lhs, double const& factor ) {
        return lhs.get() > factor;
    }

    /*!
    @brief      同じ型の変数同士で小なりイコール（≦）比較を行う
    @return     true : 左辺が右辺以下
    */
    friend bool operator<=( Derived const& lhs, Derived const& rhs ) {
        return lhs.get() <= rhs.get();
    }

    /*!
    @brief      数値との間で小なりイコール（≦）比較を行う
    @return     true : 左辺が右辺以下
    */
    friend bool operator<=( Derived const& lhs, double const& factor ) {
        return lhs.get() <= factor;
    }

    /*!
    @brief      同じ型の変数同士で大なりイコール（≧）比較を行う
    @return     true : 左辺が右辺以上
    */
    friend bool operator>=( Derived const& lhs, Derived const& rhs ) {
        return lhs.get() >= rhs.get();
    }

    /*!
    @brief      数値との間で大なりイコール（≧）比較を行う
    @return     true : 左辺が右辺以上
    */
    friend bool operator>=( Derived const& lhs, double const& factor ) {
        return lhs.get() >= factor;
    }

    /*!
    @brief      同じ型の変数同士で等価（＝）演算を行う
    @return     true : 左辺と右辺が等価
    */
    friend bool operator==( Derived const& lhs, Derived const& rhs ) {
        return lhs.get() == rhs.get();
    }

    /*!
    @brief      数値との間で等価（＝）演算を行う
    @return     true : 左辺と右辺が等価
    */
    friend bool operator==( Derived const& lhs, double const& factor ) {
        return lhs.get() == factor;
    }

    /*!
    @brief      同じ型の変数同士で不等価（＜）演算を行う
    @return     true : 左辺と右辺が不等価
    */
    friend bool operator!=( Derived const& lhs, Derived const& rhs ) {
        return lhs.get() != rhs.get();
    }

    /*!
    @brief      数値との間で不等価（＜）演算を行う
    @return     true : 左辺と右辺が不等価
    */
    friend bool operator!=( Derived const& lhs, double const& factor ) {
        return lhs.get() != factor;
    }
};

