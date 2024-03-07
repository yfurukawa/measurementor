/*!
 @file      TextFileWriter.h
 @brief     テキストファイルへの書き込み専用クラス
*/
#pragma once

// ---------------< include >----------------------------
#include "ITextFileWriter.h"

// --------------< namespace >---------------------------

// ---------< forward declaration >----------------------

/*!
 @class     TextFileWriter
 @brief     テキストファイルへの書き込み専用クラス
*/
class TextFileWriter final : public ITextFileWriter
{
public:
    /*!
    @brief  デフォルトコンストラクタ
    */
    TextFileWriter() = default;

    /*!
    @brief  デフォルトデストラクタ
    */
    virtual ~TextFileWriter();

    /*!
    @brief      ファイルをオープンする
    @param[in]  path ファイル名を含む出力先ファイルのパス
    @return     ファイルオープン失敗時の理由
    */
    std::optional<std::string> openFile( std::filesystem::path path, std::ios_base::openmode mode = std::ios_base::out ) override;

    /*!
    @brief      データを記録する
    @param[in]  content 記録する文字列
    @return     記録失敗時の理由
    */
    std::optional<std::string> write( const std::string content ) override;

    /*!
    @brief      ファイルをクローズする
    */
    std::optional<std::string> closeFile() override;

private:
    std::ofstream ofs_{};  //!< output stream
};
