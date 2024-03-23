/*!
 @file      PtsDataCollector.h
 @brief     PTSからデータを収集しメトリクスをとる
 @copyright Copyright 2024 Yoshihiro Furukawa
*/
#pragma once

// ---------------< include >----------------------------
#include <list>
#include <map>
#include <memory>
#include <string>
#include "domainPrimitives/MeasurementPrimitives.h"

// --------------< namespace >---------------------------
class Chronos;

namespace measurementor
{

// ---------< forward declaration >----------------------
class IPtsFactory;
class IPts;
class Project;
class Sprint;
class Item;
class Task;
class IAnalyzer;

/*!
 @class     PtsDataCollector
 @brief     PTSからデータを収集しメトリクスをとる
 @note      本クラスは、PTSからプロジェクトに関するデータを収集し、メトリクスが取れるよう加工した後、データベースに保存するものである。
 又、データの加工の際に一時的にデータ保存が必要なものについては、別途一時的なデータベースに保存し、それを使用する。
 PTSとのインターフェースについては、専用のクラスに依存している。
*/
class PtsDataCollector final
{
public:
  /*!
  @brief  デフォルトコンストラクタ
  */
  PtsDataCollector();

  /*!
  @brief  デフォルトデストラクタ
  */
  virtual ~PtsDataCollector();

  /*!
  @brief      Ptsからデータを収集する
  */
  void correctData();

  /*!
   @brief     Projectに関するデータを分析基盤に保存する
   @note      Projectに関するデータは、各Sprint終了時点で更新されるのでdailyで測定すれば良い
  */
  void permanentProjectData();

  /*!
   @brief     Sprintに関するデータを分析基盤に保存する
   @note      Sprintに関するデータは、Taskの状態変化を捉える必要があるので長くても30分間隔で測定する必要がある
  */
  void permanentSprintData();

protected:
  IPtsFactory* ptsFactory_;             //!< PTSとインターフェースするクラスのファクトリ
  IPts* pts_;                           //!< PTSとインターフェースするクラス
  IAnalyzer* analyzer_;                 //!< 計測データを分析するシステムとインターフェースするクラス
  std::unique_ptr<::Chronos> chronos_;  //!< 時刻情報を提供するクラス
  std::map<ProjectId, std::shared_ptr<Project>> projectList_;  //!< PTSで管理されているプロジェクトのリスト
  std::map<SprintId, std::shared_ptr<Sprint>> sprintList_;     //!< PTSで管理されているスプリンTのリスト
  std::map<ItemId, std::shared_ptr<Item>> itemList_;  //!< PTSで管理されているプロダクトバックログアイテムのリスト
  std::map<TaskId, std::shared_ptr<Task>> taskList_;  //!< PTSで管理されているタスクのリスト
  std::list<std::string> jsonObject_;                 //!< 各データクラスが生成したJSONオブジェクトの格納用

  /*!
   @brief    プロジェクトのデータを収集する
   @note     収集したデータprojectList_はに格納する
  */
  void collectProjectData();

  /*!
   @brief    スプリントのデータを収集する
   @note     収集したデータはsprintList_に格納する
  */
  void collectSprintData();

  /*!
   @brief    プロダクトバックログアイテムのデータを収集する
   @note     収集したデータはitemList_に格納する
  */
  void collectItemData();

  /*!
   @brief    タスクのデータを収集する
   @note     収集したデータはtaskList_に格納する
  */
  void collectTaskData();

  /*!
   @brief    収集したデータの内、合計する必要がある残ポイント数、残工数を集計する
  */
  void aggrigateData();

  /*!
   @brief    スプリントが持つユーザストーリポイントをプロジェクト単位で集計する
  */
  void aggrigateStoryPoint();

  /*!
   @brief    プロダクトバックログアイテムが持つ見積もり作業時間の残り時間をスプリント単位で集計する
  */
  void aggrigateRemainingWorkTime();
};

}  // namespace measurementor
