/*!
 @file      IAnalyzer.h
 @brief     データ分析システムとインターフェースするクラスのテンプレート
*/
#pragma once

// ---------------< include >----------------------------
#include <string>

// ---------< forward declaration (Global) >-------------

// --------------< namespace >---------------------------
namespace measurementor
{

// ---------< forward declaration >----------------------

/*!
 @class     IAnalyzer
 @brief     データ分析システムとインターフェースするクラスのテンプレート
 @note      本クラスは、データ分析システムへデータを登録するためのクラスのいんて-フェースを規定するものである。<br>
 具象クラスは、専用のファクトリによりインスタンス化される。
*/
class IAnalyzer
{
public:
    /*!
     @brief  デフォルトコンストラクタ
    */
    IAnalyzer() = default;

    /*!
     @brief  デフォルトデストラクタ
    */
    virtual ~IAnalyzer() = default;

    /*!
     @brief      測定データ登録
     @param[in]  登録するデータ<br>
     登録データは以下を満足したJsonオブジェクトである。<br>
     ・ネストしていない
     ・timestampフィールドが必須
     ・timestampはGMT時刻
    */
    virtual void registerMeasurementedData( const std::string& registerData ) = 0;
};

}
