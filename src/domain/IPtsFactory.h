/*!
 @file      IPtsFactory.h
 @brief     Ptsとインターフェースするクラスのファクトリの抽象クラス
*/
#pragma once

// ---------------< include >----------------------------
#include <mutex>

// --------------< namespace >---------------------------
namespace measurementor
{

// ---------< forward declaration >----------------------
class IPts;

/*!
 @class     IPtsFactory
 @brief     Ptsとインターフェースするクラスのファクトリの抽象クラス
*/
class IPtsFactory
{
public:
    /*!
    @brief  デフォルトコンストラクタ
    */
    IPtsFactory() = default;

    /*!
    @brief  デフォルトデストラクタ
    */
    virtual ~IPtsFactory() = default;

    /*!
    @brief      PtsFactoryインスタンスを生成する
    @return     PtsFactoryインスタンス
    @note       本メソッドは、各具象クラス内でPtsFactoryクラスのメソッドとして実装される。
    */
    static IPtsFactory* getInstance();

    /*!
    @brief      Ptsとインターフェースするクラスのインスタンスを生成する
    @return     Ptsとインターフェースするクラスのインスタンス
    */
    virtual IPts* createPts() = 0;

protected:
    std::mutex ptsMtx_;  //!< インスタンス生成処理保護用mutex
};

}
