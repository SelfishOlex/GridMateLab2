#include "MyProject_precompiled.h"
#include <platform_impl.h>
#include <AzCore/Memory/SystemAllocator.h>
#include <IGem.h>

#include "MyProjectSystemComponent.h"
#include "MyComponent.h"
#include "MySpawnerComponent.h"
#include <OscillatorComponent.h>

namespace MyProject
{
    class MyProjectModule
        : public CryHooksModule
    {
    public:
        AZ_RTTI(MyProjectModule,
            "{330AACA3-6D0A-4933-B887-D4EB7B78D878}",
            CryHooksModule);
        AZ_CLASS_ALLOCATOR(MyProjectModule,
            AZ::SystemAllocator, 0);

        MyProjectModule()
            : CryHooksModule()
        {
            // Push results of [MyComponent]::CreateDescriptor()
            // into m_descriptors here.
            m_descriptors.insert(m_descriptors.end(), {
                MyProjectSystemComponent::CreateDescriptor(),
                MyComponent::CreateDescriptor(),
                OscillatorComponent::CreateDescriptor(),
                MySpawnerComponent::CreateDescriptor(),
            });
        }

        /**
         * Add required SystemComponents to the SystemEntity.
         */
        AZ::ComponentTypeList
            GetRequiredSystemComponents() const override
        {
            return AZ::ComponentTypeList{
                azrtti_typeid<MyProjectSystemComponent>(),
            };
        }
    };
}

// DO NOT MODIFY THIS LINE UNLESS YOU RENAME THE GEM
// The first parameter should be GemName_GemIdLower
// The second should be
// the fully qualified name of the class above
AZ_DECLARE_MODULE_CLASS(
    MyProject_3d891812567a43af9c0f95303def50ff,
    MyProject::MyProjectModule)
