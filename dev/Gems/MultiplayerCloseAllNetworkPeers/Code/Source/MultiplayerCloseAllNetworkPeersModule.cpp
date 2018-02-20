
#include "MultiplayerCloseAllNetworkPeers_precompiled.h"
#include <platform_impl.h>

#include <AzCore/Memory/SystemAllocator.h>

#include "MultiplayerCloseAllNetworkPeersSystemComponent.h"

#include <IGem.h>

namespace MultiplayerCloseAllNetworkPeers
{
    class MultiplayerCloseAllNetworkPeersModule
        : public CryHooksModule
    {
    public:
        AZ_RTTI(MultiplayerCloseAllNetworkPeersModule, "{983AAF88-DFA3-4F14-BD1F-76F1D7F4CA69}", CryHooksModule);
        AZ_CLASS_ALLOCATOR(MultiplayerCloseAllNetworkPeersModule, AZ::SystemAllocator, 0);

        MultiplayerCloseAllNetworkPeersModule()
            : CryHooksModule()
        {
            // Push results of [MyComponent]::CreateDescriptor() into m_descriptors here.
            m_descriptors.insert(m_descriptors.end(), {
                MultiplayerCloseAllNetworkPeersSystemComponent::CreateDescriptor(),
            });
        }

        /**
         * Add required SystemComponents to the SystemEntity.
         */
        AZ::ComponentTypeList GetRequiredSystemComponents() const override
        {
            return AZ::ComponentTypeList{
                azrtti_typeid<MultiplayerCloseAllNetworkPeersSystemComponent>(),
            };
        }
    };
}

// DO NOT MODIFY THIS LINE UNLESS YOU RENAME THE GEM
// The first parameter should be GemName_GemIdLower
// The second should be the fully qualified name of the class above
AZ_DECLARE_MODULE_CLASS(MultiplayerCloseAllNetworkPeers_822389b771a4439e8edda73c4c27b953, MultiplayerCloseAllNetworkPeers::MultiplayerCloseAllNetworkPeersModule)
