/*!
 @file      PtsDataCollector.h
 @brief     PTSからデータを収集しメトリクスをとる
*/
#pragma once

// ---------------< include >----------------------------
#include <mutex>

// --------------< namespace >---------------------------
namespace measurementor
{

// ---------< forward declaration >----------------------

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
    PtsDataCollector() = default;

    /*!
    @brief  デフォルトデストラクタ
    */
    virtual ~PtsDataCollector() = default;

    /*!
    @brief      Ptsからデータを収集する
    */
    void correctData();

protected:
    
};

}
