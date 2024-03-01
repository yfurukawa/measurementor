#include <filesystem>
#include <iostream>
#include <map>
#include <memory>
#include <optional>
#include <string>
#include "ITextFileReader.h"
#include "TextFileReader.h"

int main( int argc, char* argv[] )
{
    std::filesystem::path textFile("./main.cpp");
    std::unique_ptr<TextFileReader> reader;
    reader = std::make_unique<TextFileReader>();

    auto error = reader->openFile( textFile );

    if( error )
    {
        std::cerr << error.value() << std::endl;
        exit(1);
    }

    std::optional<std::string> result;
    while( true )
    {
        result = reader->readLine();
        if( !result )
        {
            std::cout << "break" << std::endl;
            break;
        }

        std::cout << result.value() << std::endl;
        
    }

    reader->closeFile();

    return 0;
}
