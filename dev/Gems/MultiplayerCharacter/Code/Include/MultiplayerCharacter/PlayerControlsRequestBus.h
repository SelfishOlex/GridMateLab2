#pragma once
#include <AzCore/EBus/EBus.h>
#include <AzCore/Component/EntityId.h>

namespace MultiplayerCharacter
{
    // A class representing a unit measurement in degrees
    class Degree
    {
    public:
        Degree() : m_value(0) {}
        explicit Degree(float value) : m_value(value) {}
        float GetDegrees() const { return m_value; }
    private:
        float m_value;
    };

    enum class ActionState
    {
        Started,
        Stopped
    };

    class PlayerControlsRequests
        : public AZ::EBusTraits
    {
    public:
        virtual ~PlayerControlsRequests() = default;

        // EBusTraits overrides
        static const AZ::EBusHandlerPolicy HandlerPolicy =
            AZ::EBusHandlerPolicy::Single;
        static const AZ::EBusAddressPolicy AddressPolicy =
            AZ::EBusAddressPolicy::ById;
        using BusIdType = AZ::EntityId;

        // Put your public methods here
        virtual void MoveForward(ActionState state) = 0;
        virtual void MoveBackward(ActionState state) = 0;
        virtual void StrafeLeft(ActionState state) = 0;
        virtual void StrafeRight(ActionState state) = 0;
        virtual void Turn(Degree angle) = 0;
        virtual void LookUpOrDown(Degree angle) = 0;
    };

    using PlayerControlsRequestBus =
        AZ::EBus<PlayerControlsRequests>;
} // namespace MultiplayerCharacter
