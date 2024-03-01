/*!
 @file      ITextFileReader.h
 @brief     テキストファイルから読み込み専用クラスのインターフェース
*/
#pragma once

// ---------------< include >----------------------------
#include <fstream>
#include <filesystem>
#include <iostream>
#include <optional>
#include <string>

// --------------< namespace >---------------------------

// ---------< forward declaration >----------------------

/*!
 @class     ITextFileReader
 @brief     テキストファイルからの読み込み専用クラスのインターフェース
*/
class ITextFileReader
{
public:
    /*!
     @brief  デフォルトコンストラクタ
    */
    ITextFileReader() = default;

    /*!
     @brief  デフォルトデストラクタ
    */
    virtual ~ITextFileReader() = default;

    /*!
     @brief      ファイルをオープンする
     @param[in]  path ファイル名を含む読み込み元ファイルのパス
    */
    virtual std::optional<std::string> openFile( const std::filesystem::path& path ) = 0;

    /*!
     @brief      ファイルをクローズする
    */
    virtual std::optional<std::string> closeFile() = 0;
    
    /*!
     @brief    データを１行読み込む
     @return   読み込んだ文字列
    */
    virtual std::optional<std::string> readLine() = 0;

};
