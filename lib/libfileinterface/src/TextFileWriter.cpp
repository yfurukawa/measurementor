#include <iostream>
#include "TextFileWriter.h"

TextFileWriter::TextFileWriter( std::filesystem::path path )
{
    auto result = this->open( path, std::ios_base::out | std::ios_base::app );
    if( result != std::nullopt ) {
        std::cerr << result.value() << std::endl;
        exit(1);
    }
}

std::optional<std::string> TextFileWriter::open( std::filesystem::path path, std::ios_base::openmode mode )
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
