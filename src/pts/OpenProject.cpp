#include "OpenProject.h"

pts::OpenProject::OpenProject(std::unique_ptr<TcpClient> tcpClient) : tcpClient_( std::move(tcpClient) )
{
}