
#include "MyGem_precompiled.h"
#include <platform_impl.h>

#include <AzCore/Memory/SystemAllocator.h>

#include "MyGemSystemComponent.h"

#include <IGem.h>

namespace MyGem
{
    class MyGemModule
        : public CryHooksModule
    {
    public:
        AZ_RTTI(MyGemModule, "{ED7F7E70-4E86-45F4-BE71-CFE864CD0A97}", CryHooksModule);
        AZ_CLASS_ALLOCATOR(MyGemModule, AZ::SystemAllocator, 0);

        MyGemModule()
            : CryHooksModule()
        {
            // Push results of [MyComponent]::CreateDescriptor() into m_descriptors here.
            m_descriptors.insert(m_descriptors.end(), {
                MyGemSystemComponent::CreateDescriptor(),
            });
        }

        /**
         * Add required SystemComponents to the SystemEntity.
         */
        AZ::ComponentTypeList GetRequiredSystemComponents() const override
        {
            return AZ::ComponentTypeList{
                azrtti_typeid<MyGemSystemComponent>(),
            };
        }
    };
}

// DO NOT MODIFY THIS LINE UNLESS YOU RENAME THE GEM
// The first parameter should be GemName_GemIdLower
// The second should be the fully qualified name of the class above
AZ_DECLARE_MODULE_CLASS(MyGem_e3f7daf65c824319ae7304b652296d80, MyGem::MyGemModule)
