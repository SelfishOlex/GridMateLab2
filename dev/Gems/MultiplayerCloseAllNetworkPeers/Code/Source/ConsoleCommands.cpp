#include "MultiplayerCloseAllNetworkPeers_precompiled.h"
#include "ConsoleCommands.h"
#include <ISystem.h>
#include <MultiplayerCloseAllNetworkPeers/CloseNetworkPeersBus.h>

using namespace MultiplayerCloseAllNetworkPeers;

void ConsoleCommands::Register()
{
    ISystem* system = nullptr;
    CrySystemRequestBus::BroadcastResult(system,
        &CrySystemRequestBus::Events::GetCrySystem);
    if (system)
    {
        IConsole* console = system->GetIConsole();
        if (console)
        {
            console->AddCommand("closeallnetworkpeers", CloseAll,
                0, "Closes the server and all connected clients.");
        }
    }
}

void ConsoleCommands::Unregister()
{
    ISystem* system = nullptr;
    CrySystemRequestBus::BroadcastResult(system,
        &CrySystemRequestBus::Events::GetCrySystem);
    if (system)
    {
        IConsole* console = system->GetIConsole();
        if (console)
        {
            console->RemoveCommand("closeallnetworkpeers");
        }
    }
}

void ConsoleCommands::CloseAll(IConsoleCmdArgs* /*args*/)
{
    CloseNetworkPeersRequestBus::Broadcast(
        &CloseNetworkPeersRequestBus::Events::CloseAll);
}
