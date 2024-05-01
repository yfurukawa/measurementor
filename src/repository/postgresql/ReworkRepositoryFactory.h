/*!
 @file      ReworkRepositoryFactory.h
 @brief     メトリックスの計算値やその元データを保持するRepositoryクラスのファクトリクラス
 @copyright Copyright 2024 Yoshihiro Furukawa
*/
#pragma once

// ---------------< include >----------------------------
#include <filesystem>
#include <map>
#include <memory>
#include <string>
#include "../../domain/IReworkRepositoryFactory.h"
#include "ConfFileParser.h"
#include "Hostname.h"
#include "IPv4.h"
#include "ReworkRepository.h"
#include "Port.h"
#include "TcpClient.h"

// --------------< namespace >---------------------------
namespace repository
{

// ---------< forward declaration >----------------------

/*!
 @class     ReworkRepositoryFactory
 @brief     メトリックスの計算値やその元データを保持するRepositoryクラスのファクトリクラス
 @note      本クラスはメトリックスの計算値やその元データを保持するRepositoryクラスのファクトリクラスである。
 RepositoryクラスとでAbstruct Factoryパターンを形成している。
*/
class ReworkRepositoryFactory final : public measurementor::IReworkRepositoryFactory
{
public:
  /*!
  @brief  デフォルトコンストラクタ
  */
  ReworkRepositoryFactory() : repository_(nullptr)
  {
    std::filesystem::path confFile("/usr/local/etc/measurementor/postgresql.conf");  // TODO(yfurukawa) pathは別途設定できると良い
    confFileParser_ = std::make_unique<ConfFileParser>(confFile);
    ReworkRepositoryFactory::destroyed_ = false;
  }

  /*!
  @brief  デフォルトデストラクタ
  */
  virtual ~ReworkRepositoryFactory();

  /*!
  @brief      インスタンスの破棄ステータスを返す
  @return     true : インスタンス破棄済み
  */
  static const bool isDestroyed() { return ReworkRepositoryFactory::destroyed_; }

  /*!
  @brief      Repositoryインスタンスを生成する
  @return     Repositoryインスタンス
  */
  measurementor::IReworkRepository* createRepository() override
  {
    if (!repository_)
    {
      std::lock_guard<std::mutex> lock(ReworkRepositoryMtx_);
      if (!repository_)
      {
        auto result = confFileParser_->parseFile();
        if (!result)
        {
          perror(" Can not read Repository.conf");
          exit(1);
        }
        else
        {
          setting_ = result.value();
        }
        if (setting_.find("IP") != end(setting_))
        {
          repository_ = dynamic_cast<measurementor::IReworkRepository*>(new ReworkRepository(setting_["User"], setting_["Password"], setting_["IP"], setting_["Port"], setting_["DataBase"], setting_["ReworkTable"]));
        }
        else
        {
          repository_ = dynamic_cast<measurementor::IReworkRepository*>(new ReworkRepository(setting_["User"], setting_["Password"], setting_["Host"], setting_["Port"], setting_["DataBase"], setting_["ReworkTable"]));
        }
      }
    }
    return repository_;
  }

private:
  measurementor::IReworkRepository* repository_;          //!< Repositoryとインターフェースするクラス
  static bool destroyed_;                           //!< インスタンスの破棄ステータス
  std::unique_ptr<ConfFileParser> confFileParser_;  //!< confファイルのパーサ
  std::map<std::string, std::string>
    setting_;  //!< confファイルから読み込んだRepositoryサーバに関する設定（ホスト名、IPアドレス、接続先ポート、API Key）
};

}  // namespace repository
