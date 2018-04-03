#include "MyProject_precompiled.h"
#include <AzTest/AzTest.h>
#include <Tests/TestTypes.h>
#include <AzCore/std/smart_ptr/unique_ptr.h>
#include <AzCore/Component/Entity.h>
#include <AzCore/Component/TransformBus.h>
#include <OscillatorComponent.h>
#include <AzFramework/Components/TransformComponent.h>

using namespace AZ;
using namespace AzFramework;
using namespace AZStd;
using namespace MyProject;
using namespace ::testing;

class OscillatorTest
    : public ::UnitTest::AllocatorsFixture
{
    AZStd::unique_ptr<AZ::SerializeContext> m_sc;
    AZStd::unique_ptr<AZ::ComponentDescriptor> m_td;
    AZStd::unique_ptr<AZ::ComponentDescriptor> m_od;

protected:
    void SetUp() override
    {
        ::UnitTest::AllocatorsFixture::SetUp();

        // register components involved in testing
        m_sc = AZStd::make_unique<AZ::SerializeContext>();
        m_td.reset(TransformComponent::CreateDescriptor());
        m_td->Reflect(m_sc.get());
        m_od.reset(OscillatorComponent::CreateDescriptor());
        m_od->Reflect(m_sc.get());

        CreateEntity();
    }

    void CreateEntity()
    {
        // create a test entity
        e = AZStd::make_unique<Entity>();
        // OscillatorComponent is the component we are testing
        e->CreateComponent<OscillatorComponent>();
        // We can mock out Transform and test the interaction
        e->CreateComponent<AzFramework::TransformComponent>();

        // Bring the entity online
        e->Init();
        e->Activate();
    }

    unique_ptr<Entity> e;
};

TEST_F(OscillatorTest, EntityMovingUp)
{
    TransformBus::Event(e->GetId(),
        &TransformBus::Events::SetWorldTranslation,
        Vector3::CreateZero());

    TickBus::Broadcast(&TickBus::Events::OnTick, 0.1f,
            ScriptTimePoint());

    Vector3 change;
    TransformBus::EventResult(change, e->GetId(),
        &TransformBus::Events::GetWorldTranslation);

    ASSERT_TRUE(change.GetZ() > 0);
}

AZ_UNIT_TEST_HOOK();
