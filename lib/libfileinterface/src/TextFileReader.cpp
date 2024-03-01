#include <ios>
#include "TextFileReader.h"

TextFileReader::TextFileReader( std::filesystem::path path )
{
    ifs_.open(path);
}

std::optional<std::string> TextFileReader::openFile( std::filesystem::path path )
{
    if( ifs_.is_open() )
    {
        return "ファイルが既にオープンされています。";
    }
    
    ifs_.open( path, std::ios_base::in );
    if( ifs_ )
    {
        return std::nullopt;
    }
    else
    {
        return "ファイルが開けませんでした";
    }
}

std::optional<std::string> TextFileReader::close()
{
    if( !ifs_.is_open() )
    {
        return "ファイルが開かれていません";
    }
    
    ifs_.close();

    return std::nullopt;
}

std::optional<std::string> TextFileReader::readLine()
{
    std::string line("");
    std::getline( ifs_, line );
    if( (ifs_.rdstate() & std::ios_base::eofbit ) != 0 )
    {
        return line;
    }
    else
    {
        return std::nullopt;
    }
}
