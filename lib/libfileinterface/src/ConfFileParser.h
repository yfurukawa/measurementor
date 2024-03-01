/*!
 @file      ConfFileParser.h
 @brief     Linuxの標準的な設定ファイルであるconfファイルを読み込み設定値をパースする
*/
#pragma once

// ---------------< include >----------------------------
#include <filesystem>
#include <optional>
#include <string>
#include <map>

// --------------< namespace >---------------------------

// ---------< forward declaration >----------------------

/*!
 @class     ConfFileParser
 @brief     テキストファイルからの読み込み専用クラス
*/
class ConfFileParser final
{
    /*!
     @brief  デフォルトコンストラクタ
    */
    ConfFileParser() = delete;

public:
    /*!
     @brief      コンストラクタ
     @param[in]  path configファイルのパス
    */
    explicit ConfFileParser( std::filesystem::path configFile );

    /*!
     @brief  デフォルトデストラクタ
    */
    ~ConfFileParser() = default;

    /*!
     @brief      ファイルをパースする
     @param[in]  path ファイル名を含む読み込み元ファイルのパス
    */
    std::optional<std::map<std::string, std::string>> parseFile();

private:
    std::filesystem::path configFile_;   //!< configファイル
};
