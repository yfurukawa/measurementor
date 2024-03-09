#include <string>
#include "OpenProject.h"
#include "../../domain/Project.h"
#include "JsonParser.h"
#include "TcpClient.h"
#include "TextFileWriter.h"
#include "RestAPIHelper.hpp"

#include <iostream>

namespace pts
{

OpenProject::OpenProject( std::unique_ptr<::TcpClient> tcpClient, ApiKey apiKey )
    : tcpClient_( std::move(tcpClient) ),
    previousDataWriter_( std::make_unique<::TextFileWriter>() ),
    jsonParser_( std::make_unique<JsonParser>() ),
    apiKey_( apiKey )
{
}

std::list<std::map<std::string, std::string>>  OpenProject::collectAllActiveProject()
{
    std::string method("GET /api/v3/queries/available_projects");
    std::string httpVersion("HTTP/1.1");
    std::string hostLocation("Host:localhost:8080");
    std::string key(createBasicAuthorizationKey("apikey:" + apiKey_.get()));
    std::string authorizationKey("Authorization: Basic " + key);
    std::string acceptInfo("Accept: */*");
    std::string message(method + " "+ httpVersion + "\r\n" + hostLocation + "\r\n" + authorizationKey + acceptInfo + "\r\n\r\n");

    std::string receivedJson = sendQueryMessage( message );
    // TODO ここでサーバからの応答が正常であることを確認する
    std::filesystem::path previousFile("previousProject.json");
    saveJsonObjectAsPreviousData( previousFile, receivedJson );
    return jsonParser_->collectProjectData( receivedJson );
    
}

std::list<std::map<std::string, std::string>> OpenProject::collectSprintInformationOf( const measurementor::ProjectId& projectId )
{
    std::string method("GET /api/v3/projects/" + std::to_string(projectId.get()) + "/versions");
    std::string httpVersion("HTTP/1.1");
    std::string hostLocation("Host:localhost:8080");
    std::string key(createBasicAuthorizationKey("apikey:" + apiKey_.get()));
    std::string authorizationKey("Authorization: Basic " + key);
    std::string acceptInfo("Accept: */*");
    std::string message(method + " "+ httpVersion + "\r\n" + hostLocation + "\r\n" + authorizationKey + acceptInfo + "\r\n\r\n");

    std::string receivedJson = sendQueryMessage( message );
    // TODO ここでサーバからの応答が正常であることを確認する

    std::filesystem::path previousFile("previousSprint_" + std::to_string(projectId.get()) + ".json");
    saveJsonObjectAsPreviousData( previousFile, receivedJson );
    return jsonParser_->collectSprintData( receivedJson );
}

std::list<std::map<std::string, std::string>> OpenProject::collectItemInformation( const measurementor::ProjectId& projectId )
{
    std::string method("GET /api/v3/projects/" + std::to_string(projectId.get()) + "/work_packages?filters=%5b%7b%22status%22:%7b%22operator%22:%22*%22,%22alues%22:%5b%22*%22%5d%7d%7d%5d");
    std::string httpVersion("HTTP/1.1");
    std::string hostLocation("Host:localhost:8080");
    std::string key(createBasicAuthorizationKey("apikey:" + apiKey_.get()));
    std::string authorizationKey("Authorization: Basic " + key);
    std::string acceptInfo("Accept: */*");
    std::string message(method + " "+ httpVersion + "\r\n" + hostLocation + "\r\n" + authorizationKey + acceptInfo + "\r\n\r\n");

    std::string receivedJson = sendQueryMessage( message );

    // TODO ここでサーバからの応答が正常であることを確認する

    std::filesystem::path previousFile("previousItem_" + std::to_string(projectId.get()) + ".json");
    saveJsonObjectAsPreviousData( previousFile, receivedJson );
    return jsonParser_->collectItemData( receivedJson );
}

std::list<std::map<std::string, std::string>> OpenProject::collectTaskInformation( const measurementor::ProjectId& projectId )
{
    std::string method("GET /api/v3/projects/" + std::to_string(projectId.get()) + "/work_packages?filters=%5b%7b%22status%22:%7b%22operator%22:%22*%22,%22alues%22:%5b%22*%22%5d%7d%7d%5d");
    std::string httpVersion("HTTP/1.1");
    std::string hostLocation("Host:localhost:8080");
    std::string key(createBasicAuthorizationKey("apikey:" + apiKey_.get()));
    std::string authorizationKey("Authorization: Basic " + key);
    std::string acceptInfo("Accept: */*");
    std::string message(method + " "+ httpVersion + "\r\n" + hostLocation + "\r\n" + authorizationKey + acceptInfo + "\r\n\r\n");

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
    // TODO エラー処理を追加
    tcpClient_->openSocket();
    tcpClient_->sendData( queryMessage );
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
