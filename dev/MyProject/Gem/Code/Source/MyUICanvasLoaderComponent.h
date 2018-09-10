#pragma once
#include <AzCore/Component/Component.h>

namespace MyProject
{
    // Loading canvas by choice
    class MyUICanvasLoaderComponent
        : public AZ::Component
    {
    public:
        AZ_COMPONENT(MyUICanvasLoaderComponent,
            "{01AF26C5-8AD6-43A3-B439-54F384162759}");

        // AZ::Component overrides
        void Activate() override;
        void Deactivate() override {}

        static void GetRequiredServices(
            AZ::ComponentDescriptor::DependencyArrayType& prov);

        // Provide runtime reflection, if any
        static void Reflect(AZ::ReflectContext* rc);
    };
}
