
#pragma once

#include <AzCore/Component/Component.h>

#include <MultiplayerCharacter/MultiplayerCharacterBus.h>

namespace MultiplayerCharacter
{
    class MultiplayerCharacterSystemComponent
        : public AZ::Component
        , protected MultiplayerCharacterRequestBus::Handler
    {
    public:
        AZ_COMPONENT(MultiplayerCharacterSystemComponent, "{D1D1F21F-2302-4437-92EA-624BAF1A2ED4}");

        static void Reflect(AZ::ReflectContext* context);

        static void GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided);
        static void GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible);
        static void GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required);
        static void GetDependentServices(AZ::ComponentDescriptor::DependencyArrayType& dependent);

    protected:
        ////////////////////////////////////////////////////////////////////////
        // MultiplayerCharacterRequestBus interface implementation

        ////////////////////////////////////////////////////////////////////////

        ////////////////////////////////////////////////////////////////////////
        // AZ::Component interface implementation
        void Init() override;
        void Activate() override;
        void Deactivate() override;
        ////////////////////////////////////////////////////////////////////////
    };
}
