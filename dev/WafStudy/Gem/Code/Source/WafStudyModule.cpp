
#include "WafStudy_precompiled.h"
#include <platform_impl.h>

#include <AzCore/Memory/SystemAllocator.h>

#include "WafStudySystemComponent.h"

#include <IGem.h>

namespace WafStudy
{
    class WafStudyModule
        : public CryHooksModule
    {
    public:
        AZ_RTTI(WafStudyModule, "{ACD21D2F-752C-425A-B072-E0BF8507D302}", CryHooksModule);
        AZ_CLASS_ALLOCATOR(WafStudyModule, AZ::SystemAllocator, 0);

        WafStudyModule()
            : CryHooksModule()
        {
            // Push results of [MyComponent]::CreateDescriptor() into m_descriptors here.
            m_descriptors.insert(m_descriptors.end(), {
                WafStudySystemComponent::CreateDescriptor(),
            });
        }

        /**
         * Add required SystemComponents to the SystemEntity.
         */
        AZ::ComponentTypeList GetRequiredSystemComponents() const override
        {
            return AZ::ComponentTypeList{
                azrtti_typeid<WafStudySystemComponent>(),
            };
        }
    };
}

// DO NOT MODIFY THIS LINE UNLESS YOU RENAME THE GEM
// The first parameter should be GemName_GemIdLower
// The second should be the fully qualified name of the class above
AZ_DECLARE_MODULE_CLASS(WafStudy_8c965c1219084653bb3f6a17f4bf66c1, WafStudy::WafStudyModule)
