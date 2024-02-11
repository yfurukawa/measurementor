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
using IdRaw =
    StrongType<T, struct IdTag, Comparable, Printable>;
using Id = IdRaw<unsigned int>;
using ParentId  = IdRaw<unsigned int>;
using ProjectId = IdRaw<unsigned int>;
using SprintId = IdRaw<unsigned int>;
using ItemId    = IdRaw<unsigned int>;
/*
template< typename T >
using ParentIdRaw =
    StrongType<T, struct ParentIdTag, Comparable, Printable>;
using ParentId  = ParentIdRaw<unsigned int>;

template< typename T >
using ProjectIdRaw =
    StrongType<T, struct ProjectIdTag, Comparable, Printable>;
using ProjectId = ProjectIdRaw<unsigned int>;

template< typename T >
using VersionIdRaw =
    StrongType<T, struct VersionIdTag, Comparable, Printable>;
using VersionId = VersionIdRaw<unsigned int>;

template< typename T >
using ItemIdRaw =
    StrongType<T, struct ItemIdTag, Comparable, Printable>;
using ItemId    = ItemIdRaw<unsigned int>;
*/
/*!
 @def       Name
 @brief     Project、PBI及びTaskの名称
 @tparam    名称の型、文字列
*/
template< typename T >
using NameRaw =
    StrongType<T, struct NameTag, Printable>;
using Name = NameRaw<std::string>;

/*!
 @def       Point
 @brief     Product Backlog Itemの見積もりポイント
 @tparam    見積もりポイントの型、uint8_tで十分
*/
template< typename T >
using PointRaw =
    StrongType<T, struct PointTag, Addable, Printable>;
using Point = PointRaw<unsigned int>;

/*!
 @def       EstimatetTime
 @brief     タスクの見積もり時間
 @tparam    見積もり時間の型、少数点以下第1位まで表す必要がある
*/
template< typename T >
using EstimateTimeRaw =
    StrongType<T, struct ETimeTag, Addable, Printable, Swappable>;
using EstimateTime = EstimateTimeRaw<float>;

/*!
 @def       Assignee
 @brief     タスクの担当者
 @tparam    氏名の型
*/
template< typename T >
using AssigneeRaw =
    StrongType<T, struct AssigneeTag, Printable, Swappable>;
using Assignee = AssigneeRaw<std::string>;

/*!
 @def       Author
 @brief     タスクの作成者
 @tparam    氏名の型
*/
template< typename T >
using AuthorRaw =
    StrongType<T, struct AuthorTag, Printable>;
using Author = AuthorRaw<std::string>;

/*!
 @def       StartDate
 @brief     Sprintの開始日
 @tparam    日付を表す文字列
*/
template< typename T >
using StartDateRaw =
    StrongType<T, struct StartDateTag, Printable>;
using StartDate = StartDateRaw<std::string>;

/*!
 @def       EndDate
 @brief     Sprintの終了日
 @tparam    日付を表す文字列
*/
template< typename T >
using EndDateRaw =
    StrongType<T, struct EndDateTag, Printable>;
using EndDate = EndDateRaw<std::string>;

}
