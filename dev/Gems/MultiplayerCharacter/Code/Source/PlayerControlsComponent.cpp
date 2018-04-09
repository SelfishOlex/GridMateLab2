#include "MultiplayerCharacter_precompiled.h"
#include "PlayerControlsComponent.h"
#include <AzCore/Serialization/EditContext.h>
#include <LmbrCentral/Physics/CryCharacterPhysicsBus.h>
#include <AzCore/Math/Vector3.h>
#include <AzCore/Component/TransformBus.h>

using namespace MultiplayerCharacter;

void PlayerControlsComponent::Activate()
{
    PlayerControlsRequestBus::Handler::BusConnect(GetEntityId());
    AZ::TickBus::Handler::BusConnect();
}

void PlayerControlsComponent::Deactivate()
{
    PlayerControlsRequestBus::Handler::BusDisconnect();
    AZ::TickBus::Handler::BusDisconnect();
}

void PlayerControlsComponent::Reflect(AZ::ReflectContext* ref)
{
    auto sc = azrtti_cast<AZ::SerializeContext*>(ref);
    if (!sc) return;

    sc->Class<PlayerControlsComponent, Component>()
        ->Version(1);

    AZ::EditContext* ec = sc->GetEditContext();
    if (!ec) return;

    using namespace AZ::Edit::Attributes;
    // reflection of this component for Lumberyard Editor
    ec->Class<PlayerControlsComponent>("Player Controls",
        "[Implements various player controls]")
      ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
        ->Attribute(AppearsInAddComponentMenu,
            AZ_CRC("Game", 0x232b318c))
        ->Attribute(Category, "Multiplayer Character");
}

void PlayerControlsComponent::GetRequiredServices(
    AZ::ComponentDescriptor::DependencyArrayType& req)
{
    req.push_back(AZ_CRC("InputCaptureService"));
}

void PlayerControlsComponent::MoveForward(ActionState state)
{
    m_isForward = state == ActionState::Started;
}

void PlayerControlsComponent::MoveBackward(ActionState state)
{
    m_isBackward = state == ActionState::Started;
}

void PlayerControlsComponent::StrafeLeft(ActionState state)
{
    m_isStrafingLeft = state == ActionState::Started;
}

void PlayerControlsComponent::StrafeRight(ActionState state)
{
    m_isStrafingRight = state == ActionState::Started;
}

void PlayerControlsComponent::Turn(Degree angle)
{
}

void PlayerControlsComponent::LookUpOrDown(Degree angle)
{
}

void PlayerControlsComponent::OnTick(
    float dt, AZ::ScriptTimePoint)
{
    AZ::EntityId parent;
    AZ::TransformBus::EventResult(parent, GetEntityId(),
        &AZ::TransformBus::Events::GetParentId);

    AZ::Quaternion q;
    AZ::TransformBus::EventResult(q, parent,
        &AZ::TransformBus::Events::GetWorldRotationQuaternion);

    AZ::Vector3 direction = AZ::Vector3::CreateZero();

    if (m_isForward)
        direction += AZ::Vector3::CreateAxisX(1.f);
    if (m_isBackward)
        direction -= AZ::Vector3::CreateAxisX(1.f);
    if (m_isStrafingLeft)
        direction += AZ::Vector3::CreateAxisY(1.f);
    if (m_isStrafingRight)
        direction -= AZ::Vector3::CreateAxisY(1.f);

    direction *= m_speed * dt;
    direction = q * direction;

    using namespace LmbrCentral;
    CryCharacterPhysicsRequestBus::Event(parent,
        &CryCharacterPhysicsRequestBus::Events::RequestVelocity,
        direction, 0);
}
