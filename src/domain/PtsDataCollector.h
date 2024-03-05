/*!
 @file      PtsDataCollector.h
 @brief     PTSからデータを収集しメトリクスをとる
*/
#pragma once

// ---------------< include >----------------------------
#include <list>
#include <map>
#include <memory>
#include <string>
#include "../../lib/libclock/Chronos.h"
#include "Project.h"
#include "domainPrimitives/MeasurementPrimitives.h"

// --------------< namespace >---------------------------
namespace measurementor
{

// ---------< forward declaration >----------------------
class PtsFactory;
class Pts;
class Project;
class Sprint;
class Item;
class Task;

/*!
 @class     PtsDataCollector.h
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
    PtsFactory* ptsFactory_;                                        //!< PTSとインターフェースするクラス
    Pts* pts_;
    std::unique_ptr<::Chronos> chronos_;
    std::map<ProjectId, std::shared_ptr<Project>> projectList_;   //!< PTSで管理されているプロジェクトのリスト
    std::map<SprintId,  std::shared_ptr<Sprint>>  sprintList_;
    std::map<ItemId,    std::shared_ptr<Item>>    itemList_;
    std::map<TaskId,    std::shared_ptr<Task>>    taskList_;
    std::list<std::string> jsonObject_;                              //!< 各データクラスが生成したJSONオブジェクトの格納用
    

    /*!
     @brief    収集したデータの内、合計する必要がある残ポイント数、残工数を集計する
    */
    void aggrigateData();

    void collectProjectData();
    void collectSprintData();
    void collectItemData();
    void collectTaskData();
};

}
