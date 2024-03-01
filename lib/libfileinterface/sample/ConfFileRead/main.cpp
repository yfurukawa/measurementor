#include <filesystem>
#include <iostream>
#include <map>
#include <optional>
#include <string>
#include "ConfFileParser.h"

int main( int argc, char* argv[] )
{
    std::filesystem::path confFile("./sample.conf");
    ConfFileParser confParser( confFile );
    std::map<std::string, std::string> settings;

    auto result = confParser.parseFile();
    if( !result )
    {
        perror("Can not read sample.conf");
        exit(1);
    }
    else
    {
        settings = result.value();
        for( auto setting = begin(settings); setting != end(settings); ++setting )
        {
            std:: cout << setting->first << " : " << setting->second << std::endl;
        }
        
    }
    return 0;
}