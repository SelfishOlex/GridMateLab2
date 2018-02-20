
#include "WindowPosition_precompiled.h"
#include <platform_impl.h>

#include <AzCore/Memory/SystemAllocator.h>

#include "WindowPositionSystemComponent.h"

#include <IGem.h>

namespace WindowPosition
{
    class WindowPositionModule
        : public CryHooksModule
    {
    public:
        AZ_RTTI(WindowPositionModule, "{2B5A9501-0983-4F0B-8076-43B6CB159B44}", CryHooksModule);
        AZ_CLASS_ALLOCATOR(WindowPositionModule, AZ::SystemAllocator, 0);

        WindowPositionModule()
            : CryHooksModule()
        {
            // Push results of [MyComponent]::CreateDescriptor() into m_descriptors here.
            m_descriptors.insert(m_descriptors.end(), {
                WindowPositionSystemComponent::CreateDescriptor(),
            });
            /// JUST TESTING WAF
        }

        /**
         * Add required SystemComponents to the SystemEntity.
         */
        AZ::ComponentTypeList GetRequiredSystemComponents() const override
        {
            return AZ::ComponentTypeList{
                azrtti_typeid<WindowPositionSystemComponent>(),
            };
        }
    };
}

// DO NOT MODIFY THIS LINE UNLESS YOU RENAME THE GEM
// The first parameter should be GemName_GemIdLower
// The second should be the fully qualified name of the class above
AZ_DECLARE_MODULE_CLASS(WindowPosition_34891f182f464c4390e15d54b6e08636, WindowPosition::WindowPositionModule)
