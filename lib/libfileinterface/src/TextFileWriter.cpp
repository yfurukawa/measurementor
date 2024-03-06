#include <iostream>
#include "TextFileWriter.h"

std::optional<std::string> TextFileWriter::openFile( std::filesystem::path path, std::ios_base::openmode mode )
{
    try {
        ofs_.open( path.c_str(), mode );
        ofs_.exceptions( std::ios_base::failbit );
        return std::nullopt;
    }
    catch( const std::exception& e ) {
        return e.what();
    }
}

std::optional<std::string> TextFileWriter::write( const std::string content )
{
    try {
        ofs_ << content;
        return std::nullopt;
    }
    catch( const std::exception& e ) {
        return e.what();
    }
}

std::optional<std::string> TextFileWriter::closeFile()
{
    if( !ofs_.is_open() )
    {
        return "ファイルが開かれていません";
    }
    
    ofs_.close();

    return std::nullopt;
}
