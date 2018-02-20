
#include "MultiplayerCloseAllNetworkPeers_precompiled.h"

#include <AzCore/Serialization/SerializeContext.h>
#include <AzCore/Serialization/EditContext.h>

#include "MultiplayerCloseAllNetworkPeersSystemComponent.h"

namespace MultiplayerCloseAllNetworkPeers
{
    void MultiplayerCloseAllNetworkPeersSystemComponent::Reflect(AZ::ReflectContext* context)
    {
        if (AZ::SerializeContext* serialize = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serialize->Class<MultiplayerCloseAllNetworkPeersSystemComponent, AZ::Component>()
                ->Version(0)
                ->SerializerForEmptyClass();

            if (AZ::EditContext* ec = serialize->GetEditContext())
            {
                ec->Class<MultiplayerCloseAllNetworkPeersSystemComponent>("MultiplayerCloseAllNetworkPeers", "[Description of functionality provided by this System Component]")
                    ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                        ->Attribute(AZ::Edit::Attributes::AppearsInAddComponentMenu, AZ_CRC("System"))
                        ->Attribute(AZ::Edit::Attributes::AutoExpand, true)
                    ;
            }
        }
    }

    void MultiplayerCloseAllNetworkPeersSystemComponent::GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
    {
        provided.push_back(AZ_CRC("MultiplayerCloseAllNetworkPeersService"));
    }

    void MultiplayerCloseAllNetworkPeersSystemComponent::GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible)
    {
        incompatible.push_back(AZ_CRC("MultiplayerCloseAllNetworkPeersService"));
    }

    void MultiplayerCloseAllNetworkPeersSystemComponent::GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required)
    {
        (void)required;
    }

    void MultiplayerCloseAllNetworkPeersSystemComponent::GetDependentServices(AZ::ComponentDescriptor::DependencyArrayType& dependent)
    {
        (void)dependent;
    }

    void MultiplayerCloseAllNetworkPeersSystemComponent::Init()
    {
    }

    void MultiplayerCloseAllNetworkPeersSystemComponent::Activate()
    {
        MultiplayerCloseAllNetworkPeersRequestBus::Handler::BusConnect();
    }

    void MultiplayerCloseAllNetworkPeersSystemComponent::Deactivate()
    {
        MultiplayerCloseAllNetworkPeersRequestBus::Handler::BusDisconnect();
    }
}
