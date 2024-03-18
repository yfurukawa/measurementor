#include <string>
#include "OpenProject.h"
#include "../../domain/Project.h"
#include "ITcpClient.h"
#include "JsonParser.h"
#include "Logger.h"
#include "LoggerFactory.h"
#include "RestAPIHelper.h"
#include "TextFileWriter.h"


namespace pts
{

OpenProject::OpenProject( std::shared_ptr<::ITcpClient> tcpClient, ApiKey apiKey, std::string destination, unsigned int destinationPort )
    : tcpClient_( tcpClient ),
    previousDataWriter_( std::make_unique<::TextFileWriter>() ),
    jsonParser_( std::make_unique<JsonParser>() ),
    apiKey_( apiKey ),
    destination_( destination ),
    destinationPort_( destinationPort )
{
}

std::list<std::map<std::string, std::string>>  OpenProject::collectAllActiveProject()
{
    std::string message("GET /api/v3/queries/available_projects");

    std::string receivedJson = sendQueryMessage( message );
    // TODO ここでサーバからの応答が正常であることを確認する
    std::filesystem::path previousFile("previousProject.json");
    saveJsonObjectAsPreviousData( previousFile, receivedJson );
    return jsonParser_->collectProjectData( receivedJson );
    
}

std::list<std::map<std::string, std::string>> OpenProject::collectSprintInformation( const measurementor::ProjectId& projectId )
{
    std::string message("GET /api/v3/projects/" + std::to_string(projectId.get()) + "/versions");

    std::string receivedJson = sendQueryMessage( message );
    // TODO ここでサーバからの応答が正常であることを確認する

    std::filesystem::path previousFile("previousSprint_" + std::to_string(projectId.get()) + ".json");
    saveJsonObjectAsPreviousData( previousFile, receivedJson );
    return jsonParser_->collectSprintData( receivedJson );
}

std::list<std::map<std::string, std::string>> OpenProject::collectItemInformation( const measurementor::ProjectId& projectId )
{
    std::string message("GET /api/v3/projects/" + std::to_string(projectId.get()) + "/work_packages?filters=%5b%7b%22status%22:%7b%22operator%22:%22*%22,%22alues%22:%5b%22*%22%5d%7d%7d%5d");

    std::string receivedJson = sendQueryMessage( message );

    // TODO ここでサーバからの応答が正常であることを確認する

    std::filesystem::path previousFile("previousItem_" + std::to_string(projectId.get()) + ".json");
    saveJsonObjectAsPreviousData( previousFile, receivedJson );
    return jsonParser_->collectItemData( receivedJson );
}

std::list<std::map<std::string, std::string>> OpenProject::collectTaskInformation( const measurementor::ProjectId& projectId )
{
    std::string message("GET /api/v3/projects/" + std::to_string(projectId.get()) + "/work_packages?filters=%5b%7b%22status%22:%7b%22operator%22:%22*%22,%22alues%22:%5b%22*%22%5d%7d%7d%5d");

    std::string receivedJson = sendQueryMessage( message );
    // TODO ここでサーバからの応答が正常であることを確認する

    std::filesystem::path previousFile("previousTask_" + std::to_string(projectId.get()) + ".json");
    saveJsonObjectAsPreviousData( previousFile, receivedJson );
    return jsonParser_->collectTaskData( receivedJson );
}

std::string OpenProject::extractJsonFrom()
{
    std::string jsonString("");
    bool findJoson(false);

    while( !findJoson )
    {
        auto result = tcpClient_->receiveData();
        if( result )
        {
            if( isJsonString( result.value() ) )
            {
                jsonString = result.value();
                findJoson = true;
            }
        }
        else 
        {
            break;
        }
    }

    return jsonString;
}

bool OpenProject::isJsonString(std::string received)
{
    return received.find_first_of("{",0) == 0;
}

std::string OpenProject::sendQueryMessage( std::string queryMessage )
{
    std::string httpVersion("HTTP/1.1");
    std::string hostLocation("Host:" + destination_ + ":" + std::to_string( destinationPort_ ) );
    std::string key(createBasicAuthorizationKey("apikey:" + apiKey_.get()));
    std::string authorizationKey("Authorization: Basic " + key);
    std::string userAgent("User-Agent: libnet");
    std::string acceptInfo("Accept: */*");
    std::string message(queryMessage + " "+ httpVersion + "\r\n" + hostLocation + "\r\n" + authorizationKey + "\r\n" + userAgent + "\r\n" + acceptInfo + "\r\n\r\n");

    AbstLogger::LoggerFactory::getInstance()->createLogger()->log("[OpenProject] : " + queryMessage);

    // TODO エラー処理を追加
    tcpClient_->openSocket();
    tcpClient_->sendData( message );
    std::string receivedJson(extractJsonFrom());
    tcpClient_->closeSocket();
    
    return receivedJson;

}

void OpenProject::saveJsonObjectAsPreviousData( std::filesystem::path previousFile, std::string& receivedJson )
{
    previousDataWriter_->openFile( previousFile );
    auto result = previousDataWriter_->write( receivedJson );
    if( result )
    {
        std::cout << result.value() << std::endl;
    }
    previousDataWriter_->closeFile();
}

}
