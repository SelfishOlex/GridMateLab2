
#include "WafStudy_precompiled.h"

#include <AzTest/AzTest.h>

class WafStudyTest
    : public ::testing::Test
{
protected:
    void SetUp() override
    {

    }

    void TearDown() override
    {

    }
};

TEST_F(WafStudyTest, ExampleTest)
{
    ASSERT_TRUE(true);
}

AZ_UNIT_TEST_HOOK();
