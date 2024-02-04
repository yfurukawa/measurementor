/*!
 @file      PtsDataCollector.h
 @brief     PTSからデータを収集しメトリクスをとる
*/
#pragma once

// ---------------< include >----------------------------
#include <map>
#include <memory>
#include <mutex>
#include "Project.h"
#include "domainPrimitives/MeasurementPrimitives.h"

// --------------< namespace >---------------------------
namespace measurementor
{

// ---------< forward declaration >----------------------
class PtsFactory;

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

protected:
    PtsFactory* ptsFactory_;  //!< PTSとインターフェースするクラス
    std::map<unsigned int, std::shared_ptr<Project>> projectList_;   //!< PTSで管理されているプロジェクトのリスト
};

}
