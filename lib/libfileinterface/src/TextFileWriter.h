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
    @brief      コンストラクタ
    @param[in]  path ファイル名を含む出力先ファイルのパス
    */
    explicit TextFileWriter( std::filesystem::path path );

    /*!
    @brief  デフォルトデストラクタ
    */
    virtual ~TextFileWriter() {
        ofs_.flush();
        ofs_.close();
    }

    /*!
    @brief      ファイルをオープンする
    @param[in]  path ファイル名を含む出力先ファイルのパス
    @return     ファイルオープン失敗時の理由
    */
    std::optional<std::string> open( std::filesystem::path path, std::ios_base::openmode mode = std::ios_base::out ) override;

    /*!
    @brief      データを記録する
    @param[in]  content 記録する文字列
    @return     記録失敗時の理由
    */
    std::optional<std::string> write( const std::string content ) override;

private:
    std::ofstream ofs_{};  //!< output stream
};
