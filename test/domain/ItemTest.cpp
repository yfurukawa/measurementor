#include <string>
#include "ItemTest.h"
#include "../../src/domain/Item.h"
#include "../../src/domain/domainPrimitives/MeasurementPrimitives.h"

namespace measurementor
{
    void ItemTest::SetUp()
    {
    }

    void ItemTest::TearDown()
    {
        delete sut;
    }

    TEST_F(ItemTest, createJson_noAssignedTask)
    {
        Id id(1);
        Name name("Test Item");
        ProjectId projectId(10);
        Point storyPoint(3);
        EstimatedTime totalEstimatedTime(5.5);
        Status status("open");
        SprintId sprintId(12);
 
        sut = new Item( id, name, projectId, sprintId, storyPoint, status );

        std::string expected(R"({"id":1,"name":"Test Item","projectId":10,"sprintId":12,"status":"open","storyPoint":3,"totalEstimatedTime":0.0})");

        EXPECT_EQ( expected, sut->createJson() );
 
    }

}