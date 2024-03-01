/*!
 @file      TextFileReader.h
 @brief     テキストファイルから読み込み専用クラス
*/
#pragma once

// ---------------< include >----------------------------
#include <filesystem>
#include "ITextFileReader.h"

// --------------< namespace >---------------------------

// ---------< forward declaration >----------------------

/*!
 @class     TextFileReader
 @brief     テキストファイルからの読み込み専用クラス
*/
class TextFileReader final : public ITextFileReader 
{
public:
    /*!
     @brief  デフォルトコンストラクタ
    */
    TextFileReader();

    /*!
     @brief  デフォルトデストラクタ
    */
    ~TextFileReader() = default;

    /*!
     @brief      ファイルをオープンする
     @param[in]  path ファイル名を含む読み込み元ファイルのパス
    */
    std::optional<std::string> openFile( const std::filesystem::path& path ) override;

    /*!
     @brief      ファイルをクローズする
    */
    std::optional<std::string> closeFile() override;
    
    /*!
     @brief    データを１行読み込む
     @return   読み込んだ文字列
    */
    std::optional<std::string> readLine() override;

private:
    std::ifstream ifs_;   //!< ファイル読み込み用ストリーム
};
