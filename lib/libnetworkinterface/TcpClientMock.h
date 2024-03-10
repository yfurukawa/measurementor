/*!
 @file      TcpClientMock.h
 @brief     Tcp ClientMock
 @attention
*/
#pragma once

// ---------------< include >----------------------------
#include <optional>
#include <string>
#include <vector>
#include "ITcpClient.h"

// --------------< namespace >---------------------------

// ---------< forward declaration >----------------------

/*!
 @class     TcpClientMock
 @brief     TcpClientMock
 @attention
*/
class TcpClientMock final : public ITcpClient
{
public:
    /*!
    @brief  デフォルトコンストラクタ
    */
    TcpClientMock();

    /*!
    @brief  デフォルトデストラクタ
    */
    virtual ~TcpClientMock() = default;

    /*!
    @brief      データを送信する
    @param[in]  content 送信データ
    */
    void sendData( const std::string content ) const override;

    /*!
    @brief   データを受信する
    @return  受信データ。受信データが無い場合は無効値を返す
    */
    std::optional<std::string> receiveData() override;

    /*!
     @brief  TCP/IP通信のためにソケットをオープンする
    */
    void openSocket() override;
    
    /*!
     @brief  TCP/IP通信のためのソケットをクローズする
    */
    void closeSocket() override;

    /*!
     @brief  テストクラスに送信データを返す
     @return 送信されたデータ
    */
    std::vector<std::string> getSentData()
    {
        return sentData_;
    }

    /*!
     @brief  テストクラスに送信回数を返す
     @return 送信された回数
    */
    int getNumberOfSent()
    {
        return numberOfSent_;
    }

    /*!
     @brief     receiveDataメソッドが呼ばだされた際に返す文字列を設定する
     @param[in] 
    */
    void setDummyReceiveData( std::string dummy )
    {
        receiveData_ = dummy;
    }
    
private:
    mutable int numberOfSent_;                       //!< sendDataメソッドが呼び出された回数
    std::string receiveData_;                        //!< ダミーの受信データ
    mutable std::vector<std::string> sentData_;      //!< 送信を依頼された文字列

};
