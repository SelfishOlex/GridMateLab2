#include "GridMatePlayers_precompiled.h"
#include <platform_impl.h>
#include <AzCore/Memory/SystemAllocator.h>
#include <IGem.h>
#include <Components/InputCaptureComponent.h>
#include <Components/TimedProjectileComponent.h>
#include <Components/PebbleSpawnerComponent.h>
#include <Components/LocalClientComponent.h>
#include <Components/ServerAuthPlayerComponent.h>
#include <Components/ServerPlayerSpawnerComponent.h>
#include <Components/ServerPlayerControlsComponent.h>
#include <Components/LocalPredictionComponent.h>
#include <Components/InterpolationComponent.h>
#include <System/NetworkTimeSystemComponent.h>
#include <System/StartingMapSystemComponent.h>

namespace GridMatePlayers
{
    class GridMatePlayersModule
        : public CryHooksModule
    {
    public:
        AZ_RTTI(GridMatePlayersModule, "{9B7F9A35-7F93-4893-BFAF-4BE1CCD46987}", CryHooksModule);
        AZ_CLASS_ALLOCATOR(GridMatePlayersModule, AZ::SystemAllocator, 0);

        GridMatePlayersModule()
        {
            // Push results of [MyComponent]::CreateDescriptor() into m_descriptors here.
            m_descriptors.insert(m_descriptors.end(), {
                StartingMapSystemComponent::CreateDescriptor(),
                NetworkTimeSystemComponent::CreateDescriptor(),
                InputCaptureComponent::CreateDescriptor(),
                TimedProjectileComponent::CreateDescriptor(),
                PebbleSpawnerComponent::CreateDescriptor(),
                ServerPlayerSpawnerComponent::CreateDescriptor(),
                ServerAuthPlayerComponent::CreateDescriptor(),
                LocalClientComponent::CreateDescriptor(),
                ServerPlayerControlsComponent::CreateDescriptor(),
                LocalPredictionComponent::CreateDescriptor(),
                InterpolationComponent::CreateDescriptor(),
            });
        }

        /**
         * Add required SystemComponents to the SystemEntity.
         */
        AZ::ComponentTypeList GetRequiredSystemComponents() const override
        {
            return AZ::ComponentTypeList{
                azrtti_typeid<NetworkTimeSystemComponent>(),
                azrtti_typeid<StartingMapSystemComponent>(),
            };
        }
    };
}

// DO NOT MODIFY THIS LINE UNLESS YOU RENAME THE GEM
// The first parameter should be GemName_GemIdLower
// The second should be the fully qualified name of the class above
AZ_DECLARE_MODULE_CLASS(GridMatePlayers_cbf52ff874f2444381876e15e87b8a48, GridMatePlayers::GridMatePlayersModule)
