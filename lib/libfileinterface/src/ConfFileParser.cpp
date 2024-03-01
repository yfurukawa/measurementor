#include "ConfFileParser.h"
#include "TextFileReader.h"
#include <iostream>
ConfFileParser::ConfFileParser( std::filesystem::path configFile )
    : configFile_( configFile )
{
}

std::optional<std::map<std::string, std::string>> ConfFileParser::parseFile()
{
    TextFileReader fileReader;

    auto openError = fileReader.openFile( configFile_ );
    if( openError )
    {
        perror( openError.value().c_str() );
        exit(1);
    }

    std::optional<std::string> result;
    std::string line("");
    std::string key("");
    std::string value("");
    std::map<std::string, std::string> settings;
    while( true )
    {
        result = fileReader.readLine();
        if( result )
        {
            line = result.value();
            // コメント行、空行もしくは ＝ が無ければ有効な行とみなさない
            if( line.find("#") == 1 || line.empty() || line.find("=") == std::string::npos )
            {
                continue;
            }
            key = line.substr( 0, line.find("=") );
            value = line.substr( line.find("=") + 1 );
            settings.insert( std::make_pair( key, value ) );
        }
        else
        {
            break;
        }
    }

    fileReader.closeFile();

    return settings;
}
