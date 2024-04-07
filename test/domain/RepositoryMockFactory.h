/*!
 @file      RepositoryMockFactory.h
 @brief     メトリックスの計算値やその元データを保持するRepositoryMockクラスのファクトリクラス
 @copyright Copyright 2024 Yoshihiro Furukawa
*/
#pragma once

// ---------------< include >----------------------------
#include <filesystem>
#include <map>
#include <memory>
#include <string>
#include "../../src/domain/IRepositoryFactory.h"
#include "ConfFileParser.h"
#include "Hostname.h"
#include "IPv4.h"
#include "RepositoryMock.h"
#include "Port.h"
#include "TcpClient.h"

// --------------< namespace >---------------------------
namespace repository
{

// ---------< forward declaration >----------------------

/*!
 @class     RepositoryMockFactory
 @brief     メトリックスの計算値やその元データを保持するRepositoryMockクラスのファクトリクラス
 @note      本クラスはメトリックスの計算値やその元データを保持するRepositoryMockクラスのファクトリクラスである。
 RepositoryMockクラスとでAbstruct Factoryパターンを形成している。
*/
class RepositoryMockFactory final : public measurementor::IRepositoryFactory
{
public:
  /*!
  @brief  デフォルトコンストラクタ
  */
  RepositoryMockFactory() : repository_(nullptr)
  {
    /*
    std::filesystem::path confFile("/usr/local/etc/measurementor/postgresql.conf");  // TODO(yfurukawa) pathは別途設定できると良い
    confFileParser_ = std::make_unique<ConfFileParser>(confFile);
    */
    RepositoryMockFactory::destroyed_ = false;
  }

  /*!
  @brief  デフォルトデストラクタ
  */
  virtual ~RepositoryMockFactory();

  /*!
  @brief      インスタンスの破棄ステータスを返す
  @return     true : インスタンス破棄済み
  */
  static const bool isDestroyed() { return RepositoryMockFactory::destroyed_; }

  /*!
  @brief      RepositoryMockインスタンスを生成する
  @return     RepositoryMockインスタンス
  */
  measurementor::IRepository* createRepository() override
  {
    if (!repository_)
    {
      std::lock_guard<std::mutex> lock(RepositoryMtx_);
      if (!repository_)
      {
        /*
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
        */
        //if (setting_.find("IP") != end(setting_))
        //{
          repository_ = dynamic_cast<measurementor::IRepository*>(new RepositoryMock());
          // repository_ = dynamic_cast<measurementor::IRepository*>(new RepositoryMock(setting_["User"], setting_["Password"], setting_["IP"], setting_["Port"], setting_["DataBase"], setting_["Table"]));
        //}
        //else
        //{
        //  repository_ = dynamic_cast<measurementor::IRepository*>(new RepositoryMock());
          // repository_ = dynamic_cast<measurementor::IRepository*>(new RepositoryMock(setting_["User"], setting_["Password"], setting_["Host"], setting_["Port"], setting_["DataBase"], setting_["Table"]));
        //}
      }
    }
    return repository_;
  }

private:
  measurementor::IRepository* repository_;          //!< Repositoryとインターフェースするクラス
  static bool destroyed_;                           //!< インスタンスの破棄ステータス
  std::unique_ptr<ConfFileParser> confFileParser_;  //!< confファイルのパーサ
  std::map<std::string, std::string>
    setting_;  //!< confファイルから読み込んだRepositoryサーバに関する設定（ホスト名、IPアドレス、接続先ポート、API Key）
};

}  // namespace repository
