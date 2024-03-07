/*!
 @file      IAnalyzer.h
 @brief     計測値を分析するシステムとインターフェースするクラスの抽象クラス
*/
#pragma once

// ---------------< include >----------------------------

// ---------< forward declaration (Global) >-------------

// --------------< namespace >---------------------------
namespace measurementor
{

// ---------< forward declaration >----------------------

/*!
 @class     IAnalyzer
 @brief     計測値を分析するシステムとインターフェースするクラスの抽象クラス
 @note      本クラスは、メトリックスの測定値を分析するシステムとインターフェースするための抽象クラスである。<br>
 本クラスの具象クラスは、専用のファクトリクラスによりインスタンス化される。
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

};

}
