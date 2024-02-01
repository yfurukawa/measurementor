/*!
 @file      OpenProject.h
 @brief     OpenProjectとインターフェースするクラス
*/
#pragma once

// ---------------< include >----------------------------
#include <memory>
#include "../domain/Pts.h"
#include "TcpClient.h"

// --------------< namespace >---------------------------
namespace pts
{

// ---------< forward declaration >----------------------


/*!
 @class     OpenProject
 @brief     OpenProjectとインターフェースするクラス
 @note      本クラスは、OpenProjectからプロジェクトの情報を取得し、メトリックスの算出ができるように加工するクラスのためのクラスである。<br>
 本クラスは、専用のファクトリによりインスタンス化される。
*/
class OpenProject final : public measurementor::Pts
{
    /*!
     @brief  デフォルトコンストラクタ
    */
    OpenProject() = delete;
public:
    /*!
     @brief  コンストラクタ
     @param[in]  tcpClient OpenProjectと通信するためのTCPクライアント
    */
    explicit OpenProject( std::unique_ptr<TcpClient> tcpClient );

    /*!
     @brief  デフォルトデストラクタ
    */
    virtual ~OpenProject() = default;

private:
    std::unique_ptr<::TcpClient> tcpClient_;  //!< OpenProjectと通信するためのTCPクライアント

};

}
