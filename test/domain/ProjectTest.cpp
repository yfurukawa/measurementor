#include <memory>
#include <string>
#include "ProjectTest.h"
#include "../../src/domain/Project.h"
#include "../../src/domain/Item.h"
#include "../../src/domain/Sprint.h"
#include "../../src/domain/Task.h"
#include "../../src/domain/domainPrimitives/MeasurementPrimitives.h"

namespace measurementor
{
    void ProjectTest::SetUp()
    {
    }

    void ProjectTest::TearDown()
    {
        delete sut;
    }

    TEST_F(ProjectTest, createJson_noAssignedItem)
    {
        Id id(1);
        Name name("Test Project");
        ParentId parentId(10);
         
        sut = new Project( id, name, parentId );

        std::string expected(R"({"id":1,"inProgressStoryPoints":0,"name":"Test Project","remainingStoryPoints":0})");

        EXPECT_EQ( expected, sut->createJson() );
 
    }

    TEST_F(ProjectTest, createJson_TweItemsInProductBackLog)
    {
        // Item
        Id itemId(1);
        Name itemName("Test Item");
        ProjectId itemProjectId(10);
        Point storyPoint(3);
        EstimatedTime totalEstimatedTime(5.5);
        Status status("open");
        StatusCode statusCode(1);
        SprintId sprintId(12);
        std::shared_ptr<Item> item = std::make_shared<Item>( itemId, itemName, itemProjectId, sprintId, storyPoint, status, statusCode );

        Id item2Id(2);
        Name item2Name("Test Item2");
        ProjectId item2ProjectId(11);
        Point item2StoryPoint(5);
        EstimatedTime item2SotalEstimatedTime(7.0);
        Status item2Status("open");
        StatusCode item2StatusCode(1);
        SprintId item2SprintId(12);
        std::shared_ptr<Item> item2 = std::make_shared<Item>( item2Id, item2Name, item2ProjectId, item2SprintId, item2StoryPoint, item2Status, item2StatusCode );

        Id id(1);
        Name name("Test Project");
        ParentId parentId(10);
         
        sut = new Project( id, name, parentId );
        sut->addPBL( item );
        sut->addPBL( item2 );

        std::string expected(R"({"id":1,"inProgressStoryPoints":0,"name":"Test Project","remainingStoryPoints":8})");
        
        sut->aggrigateStoryPointsInPBL();
        EXPECT_EQ( expected, sut->createJson() );
 
    }

    TEST_F(ProjectTest, createJson_TweItemsInSprint)
    {
        // Item
        Id itemId(1);
        Name itemName("Test Item");
        ProjectId itemProjectId(10);
        Point storyPoint(3);
        EstimatedTime totalEstimatedTime(5.5);
        Status itemStatus("open");
        StatusCode statusCode(1);
        SprintId itemSprintId(12);
        std::shared_ptr<Item> item = std::make_shared<Item>( itemId, itemName, itemProjectId, itemSprintId, storyPoint, itemStatus, statusCode );

        Id item2Id(2);
        Name item2Name("Test Item2");
        ProjectId item2ProjectId(11);
        Point item2StoryPoint(5);
        EstimatedTime item2SotalEstimatedTime(7.0);
        Status item2Status("open");
        StatusCode item2StatusCode(1);
        SprintId item2SprintId(12);
        std::shared_ptr<Item> item2 = std::make_shared<Item>( item2Id, item2Name, item2ProjectId, item2SprintId, item2StoryPoint, item2Status, item2StatusCode );

        // Sprint
        Id sprintId(1);
        Name sprintName("Test Sprint");
        Status status("open");
        StartDate startDate("2024-02-23T12:34:56+09:00");
        EndDate endDate("2024-02-25T12:34:56+09:00");
        std::shared_ptr<Sprint> sprint = std::make_shared<Sprint>( sprintId, sprintName, status, startDate, endDate );

        sprint->addItem( item );
        sprint->addItem( item2 );

        // Project
        Id id(1);
        Name name("Test Project");
        ParentId parentId(10); 
        sut = new Project( id, name, parentId );
        sut->addSprint( sprint );

        std::string expected(R"({"id":1,"inProgressStoryPoints":8,"name":"Test Project","remainingStoryPoints":0})");
        
        sut->aggrigateStoryPointsInProgress();
        EXPECT_EQ( expected, sut->createJson() );
 
    }

}