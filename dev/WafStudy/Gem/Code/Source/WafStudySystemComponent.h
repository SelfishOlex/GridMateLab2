
#pragma once

#include <AzCore/Component/Component.h>

#include <WafStudy/WafStudyBus.h>

namespace WafStudy
{
    class WafStudySystemComponent
        : public AZ::Component
        , protected WafStudyRequestBus::Handler
    {
    public:
        AZ_COMPONENT(WafStudySystemComponent, "{1583FA65-8DCF-4848-BAE5-47DD7892CD43}");

        static void Reflect(AZ::ReflectContext* context);

        static void GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided);
        static void GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible);
        static void GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required);
        static void GetDependentServices(AZ::ComponentDescriptor::DependencyArrayType& dependent);

    protected:
        ////////////////////////////////////////////////////////////////////////
        // WafStudyRequestBus interface implementation

        ////////////////////////////////////////////////////////////////////////

        ////////////////////////////////////////////////////////////////////////
        // AZ::Component interface implementation
        void Init() override;
        void Activate() override;
        void Deactivate() override;
        ////////////////////////////////////////////////////////////////////////
    };
}
