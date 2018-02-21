
#pragma once

#include <AzCore/EBus/EBus.h>
#include <ISystem.h>
#include <IConsole.h>

namespace MultiplayerCloseAllNetworkPeers
{
    class MultiplayerCloseAllNetworkPeersRequests
        : public AZ::EBusTraits
    {
    public:
        virtual ~MultiplayerCloseAllNetworkPeersRequests() = default;

        // EBusTraits overrides
        static const AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Single;
        static const AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::Single;

        virtual void CloseAllNetworkPeers() = 0;
    };
    using MultiplayerCloseAllNetworkPeersRequestBus = AZ::EBus<MultiplayerCloseAllNetworkPeersRequests>;
} // namespace MultiplayerCloseAllNetworkPeers
