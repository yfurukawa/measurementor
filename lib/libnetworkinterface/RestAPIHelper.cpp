#include "RestAPIHelper.h"
#include "clx/base64.h"

/*!
 @fn         createBasicAuthorizationKey
 @brief      tokenからWebのBasic認証キーを生成する
 @param[in]  token 認証の基となるトークン
 @return     Basic認証キー
*/
std::string createBasicAuthorizationKey( std::string token )
{
    return clx::base64::encode( token );
}
