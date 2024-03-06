/*!
 @file      ITextFileWriter.h
 @brief     テキストファイルへの書き込み専用クラスのインターフェース
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
 @class     ITextFileWriter
 @brief     テキストファイルへの書き込み専用クラスのインターフェース
*/
class ITextFileWriter
{
public:
    /*!
    @brief  デフォルトコンストラクタ
    */
    ITextFileWriter() = default;

    /*!
    @brief  デフォルトデストラクタ
    */
    virtual ~ITextFileWriter() = default;

    /*!
    @brief      ファイルをオープンする
    @param[in]  path ファイル名を含む出力先ファイルのパス
    */
    virtual std::optional<std::string> openFile( std::filesystem::path path, std::ios_base::openmode mode = std::ios_base::out ) = 0;

    /*!
    @brief      データを記録する
    @param[in]  content 記録する文字列
    */
    virtual std::optional<std::string> write( const std::string content ) = 0;

    /*!
    @brief      ファイルをクローズする
    */
    virtual std::optional<std::string> closeFile() = 0;
};
