#include "OpenProject.h"
#include "JsonParser.h"

#include "TcpClient.h"
#include "RestAPIHelper.hpp"

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
    std::string key(createBasicAuthorizationKey("apikey:d54087631332a33b932b200c3d49496efdc7fb156b2405b2baf6fece4018e9f0"));
    std::string message("GET /api/v3/queries/available_projects HTTP/1.1\r\nHost:localhost\r\nAuthorization: Basic " + key + "\r\n\r\n");
    
    tcpClient_->sendData(message);
    std::string receivedJson(extractJsonFron());
    jsonParser_->collectProjectData( receivedJson, projectList );

}

std::string OpenProject::extractJsonFron()
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

}
