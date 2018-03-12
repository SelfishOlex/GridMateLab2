#pragma once
#include <AzCore/Component/Component.h>
#include <AzCore/Component/TickBus.h>

namespace GridMatePlayers
{
    class StartingMapSystemComponent
        : public AZ::Component
        , public AZ::SystemTickBus::Handler
    {
    public:
        AZ_COMPONENT(StartingMapSystemComponent,
            "{771A7066-45AF-4E0D-8915-04129BC64E0E}");

        static void Reflect(AZ::ReflectContext* context);

    protected:
        // AZ::Component interface implementation
        void Activate() override;
        void Deactivate() override;

        // AZ::SystemTickBus interface implementation
        void OnSystemTick() override;

    private:
        AZStd::string m_clientMap;
        AZStd::string m_serverMap;
    };
}
