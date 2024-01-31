/*!
 @file      Hostname.h
 @brief     本クラスは、ネットワークに接続されるホスト名を表すものである。
 @attention
*/
#pragma once

// ---------------< include >----------------------------
#include <string>

// --------------< namespace >---------------------------

// ---------< forward declaration >----------------------

/*!
 @class     Hostname
 @brief     本クラスは、ネットワークに接続されるホスト名を表すものであり、その形式はRFC952及びRFC1123に準拠する。
 @attention
*/
class Hostname final
{
public:
    /*!
     @brief  デフォルトコンストラクタ
    */
    Hostname() = delete;

    /*!
     @brief  コンストラクタ
     @param[in] hostname RFC952及びRFC1123に準拠したホスト名
    */
   explicit Hostname(std::string hostname);

    /*!
     @brief  デストラクタ
    */
    ~Hostname() = default;

    /*!
     @brief  コンストラクタ
     @param[in] hostname RFC952及びRFC1123に準拠したホスト名
    */
    std::string get();

private:
    std::string const hostname_;  //!< RFC952及びRFC1123に準拠したホスト名

};
