/*!
 @file      Printable.h
 @brief     強く型付けされた変数に値の出力能力を付与する
*/
#ifndef Printable_h
#define Printable_h

/*!
 @struct    Printable
 @brief     強く型付けされた変数に値の出力能力を付与する
 @tparam    Derived StrongTypeに渡されたテンプレート引数
*/
template< typename Derived >
struct Printable
{
    /*!
    @brief      output streamに値を出力する
    @return     値がセットされたoutput stream
    */
    friend std::ostream& operator<<( std::ostream& os, const Derived& d )
    {
        os << d.get();
        return os;
    }
};

#endif /* Printable_h */
