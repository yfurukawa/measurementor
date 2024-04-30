/*!
 @file      MeasurementPrimitives.h
 @brief     メトリクスを算出するために必要となるドメインプリミティブ
*/
#pragma once

// ---------------< include >----------------------------
#include <cstdint>
#include <string>
#include "StrongType.h"

// --------------< namespace >---------------------------
namespace measurementor
{

/*!
 @brief     TaskIDの型
 @tparam    TaskIdを表すのにunsigned intであれば良い
*/
template< typename T >
using TaskIdRaw =
    StrongType<T, struct TaskIdTag, Comparable, Printable>;

/*!
 @brief    実際にTaskIdとして使用する型
*/
using TaskId    = TaskIdRaw<std::uint_fast16_t>;

/*!
 @brief     ProjectIDの型
 @tparam    ProjectIdを表すのにunsigned intであれば良い
*/
template< typename T >
using ProjectIdRaw =
    StrongType<T, struct ProjectIdTag, Comparable, Printable, Swappable>;

/*!
 @brief    実際にProjectIdとして使用する型
*/
using ProjectId = ProjectIdRaw<std::uint_fast16_t>;

/*!
 @brief     SprintIDの型
 @tparam    SprintIdを表すのにunsigned intであれば良い
*/
template< typename T >
using SprintIdRaw =
    StrongType<T, struct SprintIdTag, Comparable, Printable, Swappable>;

/*!
 @brief    実際にSprintIdとして使用する型
*/
using SprintId = SprintIdRaw<std::uint_fast16_t>;

/*!
 @brief     ParentIDの型
 @tparam    ParentIdを表すのにunsigned intであれば良い
*/
template< typename T >
using ParentIdRaw =
    StrongType<T, struct ParentIdTag, Comparable, Printable>;

/*!
 @brief    実際にParentIdとして使用する型
*/
using ParentId  = ParentIdRaw<std::uint_fast16_t>;

/*!
 @brief     ItemIDの型
 @tparam    ItemIdを表すのにunsigned intであれば良い
*/
template< typename T >
using ItemIdRaw =
    StrongType<T, struct ItemIdTag, Comparable, Printable>;

/*!
 @brief    実際にItemIdとして使用する型
*/
using ItemId    = ItemIdRaw<std::uint_fast16_t>;

/*!
 @brief     Project、PBI及びTaskの名称
 @tparam    名称の型、文字列
*/
template< typename T >
using NameRaw =
    StrongType<T, struct NameTag, Printable>;

/*!
 @brief    実際にNameとして使用する型
*/
using Name = NameRaw<std::string>;

/*!
 @brief     Product Backlog Itemの見積もりポイント
 @tparam    見積もりポイントの型、uint8_tで十分
*/
template< typename T >
using PointRaw =
    StrongType<T, struct PointTag, Addable, Subtractable, Printable>;

/*!
 @brief    実際にPointとして使用する型
*/
using Point = PointRaw<std::uint_fast16_t>;

/*!
 @brief     タスクの見積もり時間
 @tparam    見積もり時間の型、少数点以下第1位まで表す必要がある
*/
template< typename T >
using EstimatedTimeRaw =
    StrongType<T, struct ETimeTag, Addable, Printable, Swappable>;

/*!
 @brief    実際にEstimatedTimeとして使用する型
*/
using EstimatedTime = EstimatedTimeRaw<double>;

/*!
 @brief     タスクの担当者
 @tparam    氏名の型
*/
template< typename T >
using AssigneeRaw =
    StrongType<T, struct AssigneeTag, Printable, Swappable>;

/*!
 @brief    実際にAssigneeとして使用する型
*/
using Assignee = AssigneeRaw<std::string>;

/*!
 @brief     タスクの作成者
 @tparam    氏名の型
*/
template< typename T >
using AuthorRaw =
    StrongType<T, struct AuthorTag, Printable>;

/*!
 @brief    実際にAuthorとして使用する型
*/
using Author = AuthorRaw<std::string>;

/*!
 @brief     elasticsearchに登録する日付
 @tparam    日付を表す文字列
 @note      フォーマットはISO8601の拡張形式GMTに準拠するが、タイムゾーンを表す"Z"は不要
*/
template< typename T >
using TimestampRaw =
    StrongType<T, struct TimestampTag, Printable, Swappable>;

/*!
 @brief    実際にTimeStampとして使用する型
*/
using Timestamp = TimestampRaw<std::string>;

/*!
 @brief     Sprintの開始日
 @tparam    日付を表す文字列
*/
template< typename T >
using StartDateRaw =
    StrongType<T, struct StartDateTag, Printable>;

/*!
 @brief    実際にStartDateとして使用する型
*/
using StartDate = StartDateRaw<std::string>;

/*!
 @brief     Sprintの終了日
 @tparam    日付を表す文字列
*/
template< typename T >
using EndDateRaw =
    StrongType<T, struct EndDateTag, Printable>;

/*!
 @brief    実際にEndDateとして使用する型
*/
using EndDate = EndDateRaw<std::string>;

/*!
 @brief     更新日
 @tparam    日付を表す文字列
*/
template< typename T >
using UpdatedAtRaw =
    StrongType<T, struct UpdatedAtTag, Printable>;

/*!
 @brief    実際にUpdateAtとして使用する型
*/
using UpdatedAt = UpdatedAtRaw<std::string>;

/*!
 @brief     ItemやTaskの状態
 @tparam    状態を表す文字列
*/
template< typename T >
using StatusRaw =
    StrongType<T, struct StatusTag, Printable, Swappable>;

/*!
 @brief    実際にStatusとして使用する型
*/
using Status = StatusRaw<std::string>;

/*!
 @brief     ItemやTaskの状態を表す番号
 @tparam    状態を表す番号
*/
template< typename T >
using StatusCodeRaw =
    StrongType<T, struct StatusCpdeTag, Comparable, Printable, Swappable>;

/*!
 @brief    実際にStatusCodeとして使用する型
*/
using StatusCode = StatusCodeRaw<std::uint_fast16_t>;

/*!
 @brief     JSONのキーを表す文字列
 @tparam    std::string
*/
template< typename T >
using JsonKeyRaw =
    StrongType<T, struct JsonKeyTag, Comparable, Printable>;

/*!
 @brief    実際にJsonKeyとして使用する型
*/
using JsonKey = JsonKeyRaw<std::string>;

/*!
 @brief     JSON Objectを表す文字列
 @tparam    std::string
*/
template< typename T >
using JsonObjectRaw =
    StrongType<T, struct JsonObjectTag, Comparable, Printable>;

/*!
 @brief    実際にJsonObjectとして使用する型
*/
using JsonObject = JsonObjectRaw<std::string>;

}
