/*!
 @file      OpenProjectFactory.h
 @brief     OpenProjectとインターフェースするクラスのファクトリクラス
 @copyright Copyright 2024 Yoshihiro Furukawa
*/
#pragma once

// ---------------< include >----------------------------
#include <filesystem>
#include <map>
#include <memory>
#include <string>
#include "../../domain/IPtsFactory.h"
#include "ConfFileParser.h"
#include "DomainPrimitivesForOpenProject.h"
#include "OpenProject.h"
#include "Port.h"

// --------------< namespace >---------------------------
namespace pts
{

// ---------< forward declaration >----------------------

/*!
 @class     OpenProjectFactory
 @brief     OpenProjectとインターフェースするクラスのファクトリクラス
 @note      本クラスはOpenProjectとインターフェースするクラスのファクトリクラスである。OpenProjectクラスとでAbstruct
 Factoryパターンを形成している。 また、OpenProjectクラスは、TcpClientを必要としているためそのインスタンスも生成している。
*/
class OpenProjectFactory final : public measurementor::IPtsFactory
{
public:
  /*!
  @brief  デフォルトコンストラクタ
  */
  OpenProjectFactory() : pts_(nullptr)
  {
    std::filesystem::path confFile("/usr/local/etc/measurementor/openproject.conf");  // TODO(yfurukawa) pathは別途設定できると良い
    confFileParser_ = std::make_unique<ConfFileParser>(confFile);
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
  static const bool isDestroyed() { return OpenProjectFactory::destroyed_; }

  /*!
  @brief      OpenProjectインスタンスを生成する
  @return     OpenProjectインスタンス
  */
  measurementor::IPts* createPts() override
  {
    if (!pts_)
    {
      std::lock_guard<std::mutex> lock(ptsMtx_);
      if (!pts_)
      {
        auto result = confFileParser_->parseFile();
        if (!result)
        {
          perror(" Can not read openproject.conf");
          exit(1);
        }
        else
        {
          setting_ = result.value();
        }
        ApiKey apiKey(setting_["apikey"]);
        pts_ = dynamic_cast<measurementor::IPts*>(new OpenProject(apiKey, ip.get(), port.get()));
      }
    }
    return pts_;
  }

private:
  measurementor::IPts* pts_;                        //!< OpenProjectとインターフェースするクラス
  static bool destroyed_;                           //!< インスタンスの破棄ステータス
  std::unique_ptr<ConfFileParser> confFileParser_;  //!< confファイルのパーサ
  std::map<std::string, std::string>
    setting_;  //!< confファイルから読み込んだOpenProjectサーバに関する設定（ホスト名、IPアドレス、接続先ポート、API Key）
};

}  // namespace pts
