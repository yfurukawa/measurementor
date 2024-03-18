/*!
 @file      IAnalyzerFactory.h
 @brief     分析システムとインターフェースするクラスのファクトリクラスのインターフェース
*/
#pragma once

// ---------------< include >----------------------------
#include <mutex>

// --------------< namespace >---------------------------
namespace measurementor
{

// ---------< forward declaration >----------------------
class IAnalyzer;

/*!
 @class     IAnalyzerFactory
 @brief     分析システムとインターフェースするクラスのファクトリクラスのインターフェース
 @note      本クラスは分析システムとインターフェースするクラスのファクトリクラスのインターフェースである。
*/
class IAnalyzerFactory
{
public:
    /*!
    @brief  デフォルトコンストラクタ
    */
    IAnalyzerFactory() = default;

    /*!
    @brief  デフォルトデストラクタ
    */
    virtual ~IAnalyzerFactory() = default;

    /*!
     @brief    Factoryのインスタンスを生成する
     @return   Factoryのインスタンス
     @note     本メソッドは、各具象クラス内でIAnalyzerFactoryクラスのメソッドとして実装される。
    */
    static IAnalyzerFactory* getInstance();

    /*!
    @brief      分析システムとインターフェースするクラスインスタンスを生成する
    @return     Elasticsearchクラスのインスタンス
    */
    virtual IAnalyzer* createIAnalyzer() = 0;

private:
    std::mutex IAnalyzerMtx_;  //!< インスタンス生成処理保護用mutex
};

}
