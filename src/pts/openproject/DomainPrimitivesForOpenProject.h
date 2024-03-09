/*!
 @file      DomainPrimitivesForOpenProject.h
 @brief     ドメインプリミティブ
*/
#pragma once

// ---------------< include >----------------------------
#include <string>
#include "StrongType.h"


/*!
 @def       ApiKey
 @brief     Basic認証のキー文字列
 @tparam    std::string
*/
template< typename T >
using ApiKeyRaw =
    StrongType<T, struct ApiKeyTag, Comparable, Printable>;
using ApiKey = ApiKeyRaw<std::string>;
