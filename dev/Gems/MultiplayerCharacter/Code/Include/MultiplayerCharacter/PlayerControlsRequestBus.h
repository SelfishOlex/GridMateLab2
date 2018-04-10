#pragma once
#include <AzCore/EBus/EBus.h>
#include <AzCore/Component/EntityId.h>

namespace MultiplayerCharacter
{
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
        virtual void Turn(float amount) = 0;
        virtual void LookUpOrDown(float amount) = 0;
    };

    using PlayerControlsRequestBus =
        AZ::EBus<PlayerControlsRequests>;
} // namespace MultiplayerCharacter
