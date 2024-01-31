/*!
 @file      NetworkParameter.h
 @brief     TCP/IP, UDP/IP通信で使用する強く型付けされた型の定義
 @attention
*/
#pragma once

// ---------------< include >----------------------------
#include <netinet/in.h>
#include <string>
#include "StrongType.h"

// --------------< namespace >---------------------------

// ---------< forward declaration >----------------------

/*!
 @def       Port
 @brief     TCP/UDPのポート番号
 @tparam    portの型、通常はuint16_tが使用される
*/
template< typename T >
using PortRaw =
    StrongType<T, struct PortTag, Comparable, Printable>;

/*!
 @def       IPv4
 @brief     IPv4形式のIPアドレス
 @tparam    IPアドレスの型、通常はstd::stringが使用される
*/
template< typename T >
using IPv4Raw =
    StrongType<T, struct IPv4Tag, Printable>;

/*!
 @def       IPv6
 @brief     IPv6形式のIPアドレス
 @tparam    IPアドレスの型、通常はstd::stringが使用される
*/
template< typename T >
using IPv6Raw =
    StrongType<T, struct IPv6Tag, Printable>;
