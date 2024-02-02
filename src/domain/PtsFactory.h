/*!
 @file      LoggerFactory.h
 @brief     LoggerFactoryの抽象クラス
*/
#pragma once

// ---------------< include >----------------------------
#include <mutex>

// --------------< namespace >---------------------------
namespace measurementor {
// ---------< forward declaration >----------------------
class Pts;

/*!
 @class     PtsFactory
 @brief     Ptsとインターフェースするクラスのファクトリの抽象クラス
*/
class PtsFactory
{
public:
    /*!
    @brief  デフォルトコンストラクタ
    */
    PtsFactory() = default;

    /*!
    @brief  デフォルトデストラクタ
    */
    virtual ~PtsFactory() = default;

    /*!
    @brief      PtsFactoryインスタンスを生成する
    @return     PtsFactoryインスタンス
    @note       本メソッドは、各具象クラス内でPtsFactoryクラスのメソッドとして実装される。
    */
    static PtsFactory* getInstance();

    /*!
    @brief      Ptsとインターフェースするクラスのインスタンスを生成する
    @return     Ptsとインターフェースするクラスのインスタンス
    */
    virtual Pts* createPts() = 0;

protected:
    std::mutex ptsMtx_;  //!< インスタンス生成処理保護用mutex
};

}
