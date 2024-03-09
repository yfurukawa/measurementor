/*!
 @file      NetworkIfHelper.h
 @brief     Networkに関する補助的な関数を提供する
 @attention
*/
#pragma once

// ---------------< include >----------------------------
#include "Hostname.h"

/*!
 @fn         resolveHostname
 @brief      ホスト名の名前解決をしてIPアドレスを得る
 @param[in]  hostname RFC952及びRFC1123に準拠したホスト名
 @return     IPアドレス（v4）
*/
std::string resolveHostname(Hostname& hostname);
