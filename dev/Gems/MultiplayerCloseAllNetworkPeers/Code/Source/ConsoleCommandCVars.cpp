#include "MultiplayerCloseAllNetworkPeers_precompiled.h"
#include "ConsoleCommandCVars.h"
#include <ISystem.h>
#include <MultiplayerCloseAllNetworkPeers/MultiplayerCloseAllNetworkPeersBus.h>
#include "MultiplayerCloseAllNetworkPeers/ShutdownApplication.h"

using namespace MultiplayerCloseAllNetworkPeers;

void ConsoleCommandCVars::RegisterCVars()
{
    if (gEnv && !gEnv->IsEditor())
    {
        REGISTER_COMMAND(m_commandName.c_str(), CloseAll, 0,
            "Closes the server and all connected clients.");
    }
}

void ConsoleCommandCVars::UnregisterCVars()
{
    if (gEnv && !gEnv->IsEditor())
    {
        UNREGISTER_CVAR(m_commandName.c_str());
    }
}

void ConsoleCommandCVars::CloseAll(IConsoleCmdArgs* /*args*/)
{
    //if (MultiplayerCloseAllNetworkPeers::MultiplayerCloseAllNetworkPeersRequestBus::FindFirstHandler())
    {
        EBUS_EVENT(MultiplayerCloseAllNetworkPeers::MultiplayerCloseAllNetworkPeersRequestBus,
            CloseAllNetworkPeers);
    }
    //else
    {
        MultiplayerCloseAllNetworkPeers::ShutdownApplication();
    }
}
