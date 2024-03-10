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

    TEST_F(IndexTest, convertCharactor_includeUpperCase)
    {
        std::string index("testIndex");
        std::string expected("testindex");

        sut = new Index( index );

        EXPECT_EQ( expected, sut->get() );
    }

    TEST_F(IndexTest, convertCharactor_includeWhiteSpace)
    {
        std::string index("test index");
        std::string expected("test_index");

        sut = new Index( index );

        EXPECT_EQ( expected, sut->get() );
    }

    TEST_F(IndexTest, convertCharactor_includeDash)
    {
        std::string index("test-index");
        std::string expected("test_index");

        sut = new Index( index );

        EXPECT_EQ( expected, sut->get() );
    }
}