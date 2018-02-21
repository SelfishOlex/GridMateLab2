
#include "MultiplayerCloseAllNetworkPeers_precompiled.h"
#include <platform_impl.h>

#include <AzCore/Memory/SystemAllocator.h>

#include "MultiplayerCloseAllNetworkPeersSystemComponent.h"
#include "CloseNetworkPeersComponent.h"
#include <IGem.h>
#include <ConsoleCommandCVars.h>

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
                MultiplayerCloseAllNetworkPeers::CloseNetworkPeersComponent::CreateDescriptor()
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

        void OnCrySystemInitialized(ISystem& system,
            const SSystemInitParams& systemInitParams) override
        {
            CryHooksModule::OnCrySystemInitialized(
                system, systemInitParams);
            m_cvars.RegisterCVars();
        }

        void OnSystemEvent(ESystemEvent event,
            UINT_PTR, UINT_PTR) override
        {
            switch (event)
            {
            case ESYSTEM_EVENT_FULL_SHUTDOWN:
            case ESYSTEM_EVENT_FAST_SHUTDOWN:
                m_cvars.UnregisterCVars();
            default:
                AZ_UNUSED(event);
            }
        }

        ConsoleCommandCVars m_cvars;
    };
}

// DO NOT MODIFY THIS LINE UNLESS YOU RENAME THE GEM
// The first parameter should be GemName_GemIdLower
// The second should be the fully qualified name of the class above
AZ_DECLARE_MODULE_CLASS(MultiplayerCloseAllNetworkPeers_822389b771a4439e8edda73c4c27b953, MultiplayerCloseAllNetworkPeers::MultiplayerCloseAllNetworkPeersModule)
