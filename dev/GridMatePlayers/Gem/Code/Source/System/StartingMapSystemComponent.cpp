#include "GridMatePlayers_precompiled.h"
#include <AzCore/Serialization/EditContext.h>
#include "StartingMapSystemComponent.h"
#include <ISystem.h>
#include <INetwork.h>
#include <GridMatePlayers/NetworkTimeRequestBus.h>

using namespace AZ;

namespace GridMatePlayers
{
    void StartingMapSystemComponent::Reflect(
        AZ::ReflectContext* context)
    {
        if (auto s = azrtti_cast<SerializeContext*>(context))
        {
            s->Class<StartingMapSystemComponent, Component>()
                ->Version(1)
                ->Field("Client Map",
                    &StartingMapSystemComponent::m_clientMap)
                ->Field("Server Map",
                    &StartingMapSystemComponent::m_serverMap);

            if (EditContext* ec = s->GetEditContext())
            {
                ec->Class<StartingMapSystemComponent>(
                    "Starting Map System Component",
                    "[Loads the starting map]")
                    ->ClassElement(
                        Edit::ClassElements::EditorData, "")
                    ->Attribute(Edit::Attributes::
                        AppearsInAddComponentMenu,
                        AZ_CRC("System"))
                    ->DataElement(nullptr,
                        &StartingMapSystemComponent::m_clientMap,
                        "Map to load on a client", "")
                    ->DataElement(nullptr,
                        &StartingMapSystemComponent::m_serverMap,
                        "Map to load on the server", "");
            }
        }
    }

    void StartingMapSystemComponent::Activate()
    {
        SystemTickBus::Handler::BusConnect();
    }

    void StartingMapSystemComponent::Deactivate()
    {
        if (SystemTickBus::Handler::BusIsConnected())
            SystemTickBus::Handler::BusDisconnect();
    }

    void StartingMapSystemComponent::OnSystemTick()
    {
        ISystem* system = nullptr;
        CrySystemRequestBus::BroadcastResult(system,
            &CrySystemRequestBus::Events::GetCrySystem);
        if (!system) return;

        IConsole* console = system->GetIConsole();
        if (!console) return;

#if defined(DEDICATED_SERVER)
        console->ExecuteString("mphost");
        console->ExecuteString(("map " + m_serverMap).c_str());
#else
        console->ExecuteString(("map " + m_clientMap).c_str());
#endif
        BusDisconnect();
    }
}
