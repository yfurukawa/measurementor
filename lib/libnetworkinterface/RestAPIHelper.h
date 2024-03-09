/*!
 @file      RestAPIHelper.h
 @brief     REST APIアクセスに関する補助的な関数を提供する
 @attention
*/
#pragma once

// ---------------< include >----------------------------
#include <string>

/*!
 @fn         createBasicAuthorizationKey
 @brief      tokenからWebのBasic認証キーを生成する
 @param[in]  token 認証の基となるトークン
 @return     Basic認証キー
*/
std::string createBasicAuthorizationKey( std::string token );