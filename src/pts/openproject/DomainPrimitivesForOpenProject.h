/*!
 @file      DomainPrimitivesForOpenProject.h
 @brief     ドメインプリミティブ
 @copyright Copyright 2024 Yoshihiro Furukawa
*/
#pragma once

// ---------------< include >----------------------------
#include <string>
#include "StrongType.h"

/*!
 @brief     Basic認証のキー文字列
 @tparam    std::string
*/
template <typename T>
using ApiKeyRaw = StrongType<T, struct ApiKeyTag, Comparable, Printable>;

/*!
 @brief    実際にapikey用に使用する型
*/
using ApiKey = ApiKeyRaw<std::string>;
