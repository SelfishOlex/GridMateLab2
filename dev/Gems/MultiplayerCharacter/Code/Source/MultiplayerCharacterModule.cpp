#include "MultiplayerCharacter_precompiled.h"
#include <platform_impl.h>
#include <AzCore/Memory/SystemAllocator.h>
#include "MultiplayerCharacterSystemComponent.h"
#include <IGem.h>
#include <PlayerControlsComponent.h>
#include <InputCaptureComponent.h>
#include <CameraControlsComponent.h>
#include <TransformSyncComponent.h>
#include <FootstepComponent.h>
#include <LocalClientComponent.h>
#include <ServerAuthPlayerComponent.h>
#include <ServerPlayerSpawnerComponent.h>
#include <PlayerActionRelayComponent.h>

namespace MultiplayerCharacter
{
    class MultiplayerCharacterModule
        : public CryHooksModule
    {
    public:
        AZ_RTTI(MultiplayerCharacterModule,
            "{3608B257-2667-4547-8DF9-1A3C030AD2FD}",
            CryHooksModule);
        AZ_CLASS_ALLOCATOR(MultiplayerCharacterModule,
            AZ::SystemAllocator, 0);

        MultiplayerCharacterModule()
        {
            // Push results of [MyComponent]::CreateDescriptor()
            // into m_descriptors here.
            m_descriptors.insert(m_descriptors.end(), {
                MultiplayerCharacterSystemComponent::CreateDescriptor(),
                PlayerControlsComponent::CreateDescriptor(),
                CameraControlsComponent::CreateDescriptor(),
                InputCaptureComponent::CreateDescriptor(),
                TransformSyncComponent::CreateDescriptor(),
                FootstepComponent::CreateDescriptor(),
                LocalClientComponent::CreateDescriptor(),
                ServerAuthPlayerComponent::CreateDescriptor(),
                ServerPlayerSpawnerComponent::CreateDescriptor(),
                PlayerActionRelayComponent::CreateDescriptor(),
            });
        }

        /**
         * Add required SystemComponents to the SystemEntity.
         */
        AZ::ComponentTypeList GetRequiredSystemComponents() const override
        {
            return AZ::ComponentTypeList{
                azrtti_typeid<MultiplayerCharacterSystemComponent>(),
            };
        }
    };
}

// DO NOT MODIFY THIS LINE UNLESS YOU RENAME THE GEM
// The first parameter should be GemName_GemIdLower
// The second should be the fully qualified name of the class
AZ_DECLARE_MODULE_CLASS(
    MultiplayerCharacter_6f05cbbd30e0470784094f854745edf1,
    MultiplayerCharacter::MultiplayerCharacterModule)
