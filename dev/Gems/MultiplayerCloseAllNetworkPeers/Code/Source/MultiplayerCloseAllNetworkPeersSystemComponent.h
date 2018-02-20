
#pragma once

#include <AzCore/Component/Component.h>

#include <MultiplayerCloseAllNetworkPeers/MultiplayerCloseAllNetworkPeersBus.h>

namespace MultiplayerCloseAllNetworkPeers
{
    class MultiplayerCloseAllNetworkPeersSystemComponent
        : public AZ::Component
        , protected MultiplayerCloseAllNetworkPeersRequestBus::Handler
    {
    public:
        AZ_COMPONENT(MultiplayerCloseAllNetworkPeersSystemComponent, "{30168C7B-5DCE-4404-83DC-6349CB07A60F}");

        static void Reflect(AZ::ReflectContext* context);

        static void GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided);
        static void GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible);
        static void GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required);
        static void GetDependentServices(AZ::ComponentDescriptor::DependencyArrayType& dependent);

    protected:
        ////////////////////////////////////////////////////////////////////////
        // MultiplayerCloseAllNetworkPeersRequestBus interface implementation

        ////////////////////////////////////////////////////////////////////////

        ////////////////////////////////////////////////////////////////////////
        // AZ::Component interface implementation
        void Init() override;
        void Activate() override;
        void Deactivate() override;
        ////////////////////////////////////////////////////////////////////////
    };
}
