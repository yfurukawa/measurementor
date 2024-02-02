#include <string>
#include "OpenProject.h"
#include "../domain/Project.h"
#include <iostream>

namespace pts
{

OpenProject::OpenProject(std::unique_ptr<::TcpClient> tcpClient) : tcpClient_( std::move(tcpClient) )
{
    projectList_.clear();
}

std::list<measurementor::Project> OpenProject::collectAllActiveProject()
{
    // TODO
    std::string message("GET /api/v3/projects HTTP/1.1\r\nHost:localhost\r\nAuthorization: Basic YXBpa2V5OjQ2YmQ3YTg0NDY5NDRiOWRhMDhjODRjMjZjYzE0MTg4Yzg4ZDg5NDg2NWU0NDc1ZGU4YzI5M2Q0Y2E5YTk0Y2U=\r\n\r\n");
    tcpClient_->sendData(message);
    std::string receivedJson;;
    while(true)
    {
        auto result = tcpClient_->receiveData();
        if( result )
        {
            receivedJson = result.value();
        }
        else 
        {
            break;
        }
        std::cout << receivedJson << std::endl;
        std::cout << "----------------------------------------------" << std::endl;
    }
    std::list<measurementor::Project> projectList;
    return projectList;
}

}
