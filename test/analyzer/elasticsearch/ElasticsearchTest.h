/*!
 @file      ElasticsearchTest.h
 @brief     Elasticsearchをテストする
*/
#pragma once

// ---------------< include >----------------------------
#include <gtest/gtest.h>

// --------------< namespace >---------------------------
namespace analyzer
{

// ---------< forward declaration >----------------------
class Elasticsearch;

/*!
 @file      ElasticsearchTest.h
 @brief     Elasticsearchをテストする
*/
class ElasticsearchTest : public ::testing::Test
{
public:
    /*!
     @brief  デフォルトコンストラクタ
    */
    ElasticsearchTest() = default;

    /*!
     @brief  デフォルトデストラクタ
    */
    virtual ~ElasticsearchTest() = default;

protected:
    Elasticsearch* sut;

    void SetUp();
    void TearDown();
};

}
