/*!
 @file      OpenProjectFactory.h
 @brief     OpenProjectとインターフェースするクラスのファクトリクラス
*/
#pragma once

// ---------------< include >----------------------------
#include <memory>
#include "../../domain/PtsFactory.h"
#include "IPv4.h"
#include "OpenProject.h"
#include "TcpClient.h"
#include "Port.h"
#include "Hostname.h"

// --------------< namespace >---------------------------
namespace pts
{

// ---------< forward declaration >----------------------

/*!
 @class     OpenProjectFactory
 @brief     OpenProjectとインターフェースするクラスのファクトリクラス
 @note      本クラスはOpenProjectとインターフェースするクラスのファクトリクラスである。OpenProjectクラスとでAbstruct Factoryパターンを形成している。
 また、OpenProjectクラスは、TcpClientを必要としているためそのインスタンスも生成している。
*/
class OpenProjectFactory final : public measurementor::PtsFactory
{
public:
    /*!
    @brief  デフォルトコンストラクタ
    */
    OpenProjectFactory() {
        OpenProjectFactory::destroyed_ = false;
    }

    /*!
    @brief  デフォルトデストラクタ
    */
    virtual ~OpenProjectFactory();

    /*!
    @brief      インスタンスの破棄ステータスを返す
    @return     true : インスタンス破棄済み
    */
    static const bool isDestroyed() {
        return OpenProjectFactory::destroyed_;
    }

    /*!
    @brief      Loggerインスタンスを生成する
    @return     ToSyslogLoggerインスタンス
    */
    measurementor::Pts* createPts() override
    {
        if( !pts_ ) {
            std::lock_guard<std::mutex> lock(ptsMtx_);
            if( !pts_ ) {
                IPv4 ip("127.0.0.1");
                Port port(8080);
                pts_ = dynamic_cast<measurementor::Pts*>( new OpenProject( std::make_unique<::TcpClient>( ip, port ) ) );
            }
        }
        return pts_;
    }

private:
    static bool destroyed_;    //!< インスタンスの破棄ステータス
    measurementor::Pts* pts_{nullptr};  //!< 具象クラスのインスタンス
};

}
