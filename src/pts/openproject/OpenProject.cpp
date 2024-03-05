#include "OpenProject.h"
#include "../../domain/Project.h"
#include "JsonParser.h"
#include "TcpClient.h"
#include "RestAPIHelper.hpp"

#include <iostream>

namespace pts
{

OpenProject::OpenProject( std::unique_ptr<::TcpClient> tcpClient, ApiKey apiKey )
    : tcpClient_( std::move(tcpClient) ),
    jsonParser_( std::make_unique<JsonParser>() ),
    apiKey_( apiKey )
{
}

std::list<std::map<std::string, std::string>>  OpenProject::collectAllActiveProject()
{
    std::string key(createBasicAuthorizationKey("apikey:" + apiKey_.get()));
    std::string message("GET /api/v3/queries/available_projects HTTP/1.1\r\nHost:localhost:8080\r\nAuthorization: Basic " + key + "\r\n\r\n");

    std::string receivedJson = sendQueryMessage( message );
    // TODO ここでサーバからの応答が正常であることを確認する
    return jsonParser_->collectProjectData( receivedJson );
    
}

std::list<std::map<std::string, std::string>> OpenProject::collectSprintInformationOf( measurementor::ProjectId& projectId )
{
    std::string key(createBasicAuthorizationKey("apikey:" + apiKey_.get()));
    std::string message("GET /api/v3/projects/" + std::to_string(projectId.get()) + "/versions HTTP/1.1\r\nHost:localhost:8080\r\nAuthorization: Basic " + key + "\r\n\r\n");
    
    std::string receivedJson = sendQueryMessage( message );
    // TODO ここでサーバからの応答が正常であることを確認する
    return jsonParser_->collectSprintData( receivedJson );
}

std::list<std::map<std::string, std::string>> OpenProject::collectItemInformation( measurementor::ProjectId& projectId )
{
    std::string key(createBasicAuthorizationKey("apikey:" + apiKey_.get()));
    std::string message("GET /api/v3/projects/" + std::to_string(projectId.get()) + "/work_packages?filters=%5b%7b%22status%22:%7b%22operator%22:%22*%22,%22alues%22:%5b%22*%22%5d%7d%7d%5d HTTP/1.1\r\nHost:localhost:8080\r\nAuthorization: Basic " + key + "\r\n\r\n");
    
    std::string receivedJson = sendQueryMessage( message );
    // TODO ここでサーバからの応答が正常であることを確認する
    jsonParser_->collectItemData( receivedJson );
}

std::list<std::map<std::string, std::string>> OpenProject::collectTaskInformation( measurementor::ProjectId& projectId )
{
    std::string key(createBasicAuthorizationKey("apikey:" + apiKey_.get()));
    std::string message("GET /api/v3/projects/" + std::to_string(projectId.get()) + "/work_packages?filters=%5b%7b%22status%22:%7b%22operator%22:%22*%22,%22alues%22:%5b%22*%22%5d%7d%7d%5d HTTP/1.1\r\nHost:localhost:8080\r\nAuthorization: Basic " + key + "\r\n\r\n");
    
    std::string receivedJson = sendQueryMessage( message );
    // TODO ここでサーバからの応答が正常であることを確認する
    jsonParser_->collectTaskData( receivedJson );
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
    tcpClient_->openSocket();
    tcpClient_->sendData( queryMessage );
    std::string receivedJson(extractJsonFrom());
    tcpClient_->closeSocket();
    
    return receivedJson;

}

}
