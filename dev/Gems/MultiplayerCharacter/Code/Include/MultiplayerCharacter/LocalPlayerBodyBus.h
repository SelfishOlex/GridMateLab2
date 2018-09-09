#pragma once
#include <AzCore/EBus/EBus.h>
#include <GridMate/Session/Session.h>
#include <AzCore/Component/EntityId.h>

namespace MultiplayerCharacter
{
    class LocalPlayerBodyInterface
        : public AZ::ComponentBus
    {
    public:
        virtual ~LocalPlayerBodyInterface() = default;

        virtual void OnClientInputConnected() = 0;
    };

    using LocalPlayerBodyNotificationBus =
        AZ::EBus<LocalPlayerBodyInterface>;
} // namespace MultiplayerCharacter
