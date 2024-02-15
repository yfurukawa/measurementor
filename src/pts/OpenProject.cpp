#include "OpenProject.h"
#include "../domain/Project.h"
#include "JsonParser.h"
#include "TcpClient.h"
#include "RestAPIHelper.hpp"

#include <iostream>

namespace pts
{

OpenProject::OpenProject(std::unique_ptr<::TcpClient> tcpClient)
    : tcpClient_( std::move(tcpClient) ),
    jsonParser_( std::make_unique<JsonParser>() )
{
}

void OpenProject::collectAllActiveProject( std::map<unsigned int,std::shared_ptr<measurementor::Project>>& projectList )
{
    // TODO tokenはファイルから読み込むようにする
    std::string key(createBasicAuthorizationKey("apikey:8674616b3d0fbbff8c4601345bd36774a49341ef73ae54609daca068aebf74b0"));
    std::string message("GET /api/v3/queries/available_projects HTTP/1.1\r\nHost:localhost:8080\r\nAuthorization: Basic " + key + "\r\n\r\n");

    std::string receivedJson = sendQueryMessage( message );
    jsonParser_->collectProjectData( receivedJson, projectList );
    
}

void OpenProject::collectSprintInformationOf( std::shared_ptr<measurementor::Project>& project )
{
    // TODO tokenはファイルから読み込むようにする
    std::string key(createBasicAuthorizationKey("apikey:8674616b3d0fbbff8c4601345bd36774a49341ef73ae54609daca068aebf74b0"));
    std::string message("GET /api/v3/projects/" + std::to_string(project->id().get()) + "/versions HTTP/1.1\r\nHost:localhost:8080\r\nAuthorization: Basic " + key + "\r\n\r\n");
    
    std::string receivedJson = sendQueryMessage( message );
    jsonParser_->collectSprintData( receivedJson, project );
    //std::cout << receivedJson << std::endl;
}

void OpenProject::collectPBLandTaskInformation( std::shared_ptr<measurementor::Project>& project )
{
    // TODO tokenはファイルから読み込むようにする
    std::string key(createBasicAuthorizationKey("apikey:8674616b3d0fbbff8c4601345bd36774a49341ef73ae54609daca068aebf74b0"));
    std::string message("GET /api/v3/projects/" + std::to_string(project->id().get()) + "/work_packages?filters=%5b%7b%22status%22:%7b%22operator%22:%22*%22,%22alues%22:%5b%22*%22%5d%7d%7d%5d HTTP/1.1\r\nHost:localhost:8080\r\nAuthorization: Basic " + key + "\r\n\r\n");
    
    std::string receivedJson = sendQueryMessage( message );
    jsonParser_->collectPBLandTaskData( receivedJson, project );
    //std::cout << receivedJson << std::endl;

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
