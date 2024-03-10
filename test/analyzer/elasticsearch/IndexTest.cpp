#include <string>
#include "IndexTest.h"
#include "../../../src/analyzer/elasticsearch/Index.h"

namespace analyzer
{
    void IndexTest::SetUp()
    {
    }

    void IndexTest::TearDown()
    {
        delete sut;
    }

    TEST_F(IndexTest, get)
    {
        std::string index("testindex");
        std::string expected("testindex");

        sut = new Index( index );

        EXPECT_EQ( expected, sut->get() );
    }

}