#include "MultiplayerCloseAllNetworkPeers_precompiled.h"
#include <MultiplayerCloseAllNetworkPeers/ShutdownApplication.h>
#include <ISystem.h>
#include <IConsole.h>

void MultiplayerCloseAllNetworkPeers::ShutdownApplication()
{
    ISystem* system = nullptr;
    EBUS_EVENT_RESULT(system, CrySystemRequestBus, GetCrySystem);
    if (system)
    {
        system->GetIConsole()->ExecuteString("quit");
    }
}
