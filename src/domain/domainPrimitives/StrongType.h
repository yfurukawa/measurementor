/*!
 @file      StrongType.h
 @brief     強く型付けされた変数のテンプレート
 @attention 本コードは書籍「C++ソフトウェア設計」 ISBN 9784814400454　からの引用である。<br>
 本定義単体では使用不可。別途変数を定義すること。
*/
#ifndef StrongType_h
#define StrongType_h

#include <utility>
#include "skills/Addable.h"
#include "skills/Comparable.h"
#include "skills/Printable.h"
#include "skills/Swappable.h"

/*!
 @struct    StrongType
 @brief     強く型付けされた変数のテンプレート
 @tparam    T 保持する値のプリミティブ型
 @tparam    Tag 定義する強く型付けされた変数の識別用タグ
 @tparam    class 強く型付けされた変数が実行できるオペレーション
*/
template< typename T, typename Tag, template<typename> class... Skills >
struct StrongType : private Skills< StrongType<T, Tag, Skills...> >...
{
public:
    using value_type = T;

    /*!
    @brief      コンストラクタ
    @param[in]  value 変数の値
    */
    explicit StrongType( T const& value ) : value_( value ) {}
    
    /*!
    @brief      値取得
    @return     保持している値
    */
    T&       get()       { return value_; }

    /*!
    @brief      値取得
    @return     保持している値
    */
    T const& get() const { return value_; }

private:
    T value_;    //!< 変数の値
};

#endif /* StrongType_h */
