#include <memory>
#include <new>
#include <string>
#include "ElasticsearchTest.h"
#include "ITcpClient.h"
#include "TcpClientMock.h"
#include "../../../src/analyzer/elasticsearch/Elasticsearch.h"
#include "../../../src/analyzer/elasticsearch/DomainPrimitivesForElasticasearch.h"

namespace analyzer
{
    void ElasticsearchTest::SetUp()
    {
    }

    void ElasticsearchTest::TearDown()
    {
        delete sut;
    }

    TEST_F(ElasticsearchTest, get)
    {
        std::shared_ptr<::TcpClientMock> tcpClient = std::make_shared<::TcpClientMock>();
        ApiKey apiKey("dummy");
        Version version("8.12.1");
        std::string index("testindex");

        std::string expected("POST /testindex/_doc/ HTTP/1.1\r\nHost:localhost:9200\r\nUser-Agent: libnet\r\nAccept: */*\r\nContent-Type: application/json; charset=UTF-8\r\nContent-Length: 4\r\ntest\r\n\r\n");

        sut = new Elasticsearch( tcpClient, apiKey, version, index );
        sut->registerMeasurementedData( "test");

        EXPECT_EQ( expected, tcpClient->getSentData().at(0) );
    }

}