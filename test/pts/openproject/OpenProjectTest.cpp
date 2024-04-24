#include <memory>
#include <string>
#include "ITcpClient.h"
#include "OpenProjectTest.h"
#include "TcpClientMock.h"
#include "../../../src/pts/openproject/JsonParser.h"
#include "../../../src/pts/openproject/OpenProject.h"
#include "../../../src/pts/openproject/DomainPrimitivesForOpenProject.h"

namespace pts
{
    void OpenProjectTest::SetUp()
    {
    }

    void OpenProjectTest::TearDown()
    {
        delete sut;
    }

    TEST_F(OpenProjectTest, collectAllActiveProject)
    {
        std::shared_ptr<::TcpClientMock> tcpClient = std::make_shared<::TcpClientMock>();
        ApiKey apiKey("dumy");
        std::string received( R"({"dummy":"dummy"})" );
        tcpClient->setDummyReceiveData( received );

        std::string expected("GET /api/v3/projects?pageSize=1000 HTTP/1.1\r\nHost:localhost:8080\r\nAuthorization: Basic YXBpa2V5OmR1bXk=\r\nUser-Agent: libnet\r\nAccept: */*\r\n\r\n");

        sut = new OpenProject(tcpClient, apiKey, "localhost", 8080);
        sut->collectAllActiveProject();

        EXPECT_EQ( expected, tcpClient->getSentData().at(0) );
    }

}
