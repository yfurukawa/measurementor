#include "ConfFileParser.h"
#include "TextFileReader.h"

ConfFileParser::ConfFileParser( std::filesystem::path configFile )
    : configFile_( configFile )
{
}

std::optional<std::map<std::string, std::string>> ConfFileParser::parseFile()
{
    TextFileReader fileReader( configFile_ );
    std::string line("");
    std::optional<std::string> result;
    std::string key("");
    std::string value("");
    std::map<std::string, std::string> settings;

    while( !(result = fileReader.readLine()) )
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
    
    return settings;
}
