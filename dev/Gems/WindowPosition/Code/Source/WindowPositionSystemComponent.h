
#pragma once

#include <AzCore/Component/Component.h>

#include <WindowPosition/WindowPositionBus.h>

namespace WindowPosition
{
    class WindowPositionSystemComponent
        : public AZ::Component
        , protected WindowPositionRequestBus::Handler
    {
    public:
        AZ_COMPONENT(WindowPositionSystemComponent, "{46E6C884-3C92-46B3-B3F2-42F993536499}");

        static void Reflect(AZ::ReflectContext* context);

        static void GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided);
        static void GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible);
        static void GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required);
        static void GetDependentServices(AZ::ComponentDescriptor::DependencyArrayType& dependent);

    protected:
        ////////////////////////////////////////////////////////////////////////
        // WindowPositionRequestBus interface implementation

        ////////////////////////////////////////////////////////////////////////

        ////////////////////////////////////////////////////////////////////////
        // AZ::Component interface implementation
        void Init() override;
        void Activate() override;
        void Deactivate() override;
        ////////////////////////////////////////////////////////////////////////
    };
}
