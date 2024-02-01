/*!
 @file      MeasurementPrimitives.h
 @brief     メトリクスを算出するために必要となるドメインプリミティブ
*/
#pragma once

// ---------------< include >----------------------------
#include <string>
#include "StrongType.h"

// --------------< namespace >---------------------------
namespace measurementor
{

/*!
 @def       Id
 @brief     Project、PBI及びTaskのID
 @tparam    IDの型
*/
template< typename T >
using Id =
    StrongType<T, struct IdTag, Printable>;

/*!
 @def       Name
 @brief     Project、PBI及びTaskの名称
 @tparam    名称の型、文字列
*/
template< typename T >
using Name =
    StrongType<T, struct NameTag, Printable>;

/*!
 @def       Point
 @brief     Product Backlog Itemの見積もりポイント
 @tparam    見積もりポイントの型、uint8_tで十分
*/
template< typename T >
using Point =
    StrongType<T, struct PointTag, Addable, Printable>;

/*!
 @def       EstimatetTime
 @brief     タスクの見積もり時間
 @tparam    見積もり時間の型、少数点以下第1位まで表す必要がある
*/
template< typename T >
using EstimatetTime =
    StrongType<T, struct ETimeTag, Addable, Printable>;

}
