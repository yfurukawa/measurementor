/*!
 @file      OpenProject.h
 @brief     OpenProjectとインターフェースするクラス
*/
#pragma once

// ---------------< include >----------------------------
#include <list>
#include <memory>
#include "../domain/Pts.h"

// ---------< forward declaration (Global) >-------------
class TcpClient;

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

    /*!
     @brief  全てのアクティブプロジェクトを収集する
     @return アクティブプロジェクトのリスト
    */
    std::list<measurementor::Project> collectAllActiveProject() override;

private:
    std::unique_ptr<::TcpClient> tcpClient_;  //!< OpenProjectと通信するためのTCPクライアント
};

}
