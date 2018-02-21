#include "MultiplayerCloseAllNetworkPeers_precompiled.h"
#include <AzCore/Serialization/EditContext.h>
#include "MultiplayerCloseAllNetworkPeersSystemComponent.h"
#include <INetwork.h>
#include <AzFramework/Network/NetBindingComponent.h>
#include "CloseNetworkPeersComponent.h"
#include "AzFramework/Entity/GameEntityContextBus.h"
#include <MultiplayerCloseAllNetworkPeers/ShutdownApplication.h>

using namespace AZ;
using namespace AzFramework;
using namespace GridMate;

namespace MultiplayerCloseAllNetworkPeers
{
    void MultiplayerCloseAllNetworkPeersSystemComponent::Reflect(ReflectContext* context)
    {
        if (auto sc = azrtti_cast<SerializeContext*>(context))
        {
            sc->Class<MultiplayerCloseAllNetworkPeersSystemComponent, Component>()
                ->Version(0)->SerializerForEmptyClass();

            if (auto ec = sc->GetEditContext())
            {
                ec->Class<MultiplayerCloseAllNetworkPeersSystemComponent>(
                    "Close All Network Peers",
                    "[Closes all connected network peers]")
                ->ClassElement(
                    Edit::ClassElements::EditorData, "")
                ->Attribute(Edit::Attributes::
                    AppearsInAddComponentMenu,AZ_CRC("System"))
                ->Attribute(Edit::Attributes::AutoExpand, true);
            }
        }
    }

    void MultiplayerCloseAllNetworkPeersSystemComponent::GetProvidedServices(
        AZ::ComponentDescriptor::DependencyArrayType& provided)
    {
        provided.push_back(AZ_CRC("CloseAllPeersService"));
    }

    void MultiplayerCloseAllNetworkPeersSystemComponent::GetIncompatibleServices(
        AZ::ComponentDescriptor::DependencyArrayType& incompat)
    {
        incompat.push_back(AZ_CRC("CloseAllPeersService"));
    }

    void MultiplayerCloseAllNetworkPeersSystemComponent::GetRequiredServices(
        AZ::ComponentDescriptor::DependencyArrayType& required)
    {
        (void)required;
    }

    void MultiplayerCloseAllNetworkPeersSystemComponent::GetDependentServices(
        AZ::ComponentDescriptor::DependencyArrayType& dependent)
    {
        (void)dependent;
    }

    void MultiplayerCloseAllNetworkPeersSystemComponent::CloseAllNetworkPeers()
    {
        if (CloseAllRequestBus::FindFirstHandler())
        {
            EBUS_EVENT(CloseAllRequestBus, CloseAll);
        }
        else
        {
            MultiplayerCloseAllNetworkPeers::ShutdownApplication();
        }
    }

    void MultiplayerCloseAllNetworkPeersSystemComponent::Activate()
    {
        MultiplayerCloseAllNetworkPeersRequestBus::Handler::BusConnect();
        GameEntityContextEventBus::Handler::BusConnect();
        CrySystemEventBus::Handler::BusConnect();
    }

    void MultiplayerCloseAllNetworkPeersSystemComponent::Deactivate()
    {
        MultiplayerCloseAllNetworkPeersRequestBus::Handler::BusDisconnect();
        GameEntityContextEventBus::Handler::BusDisconnect();
        CrySystemEventBus::Handler::BusDisconnect();
    }

    void MultiplayerCloseAllNetworkPeersSystemComponent::OnGameEntitiesStarted()
    {
        AZ_Printf("", "OnGameEntitiesStarted");
        m_isMapLoaded = true;

        if (m_isHost && m_workerEntity == nullptr)
        {
            AZ_Printf("", "OnGameEntitiesStarted - Entity");
            CreateWorkerEntity();
        }
    }

    void MultiplayerCloseAllNetworkPeersSystemComponent::OnGameEntitiesReset()
    {
        m_workerEntity = nullptr;
        m_isMapLoaded = false;
    }

    void MultiplayerCloseAllNetworkPeersSystemComponent::OnSessionHosted(
        GridMate::GridSession* session)
    {
        AZ_Printf("", "OnSessionHosted");
        m_isHost = true;

        if (m_isMapLoaded && m_workerEntity == nullptr)
        {
            AZ_Printf("", "OnGameEntitiesStarted - Entity");
            CreateWorkerEntity();
        }
    }

    void MultiplayerCloseAllNetworkPeersSystemComponent::OnSessionDelete(
        GridMate::GridSession*)
    {
        m_isHost = false;
    }

    void MultiplayerCloseAllNetworkPeersSystemComponent::OnSessionEnd(
        GridMate::GridSession*)
    {
        m_isHost = false;
    }

    void MultiplayerCloseAllNetworkPeersSystemComponent::OnCrySystemInitialized(
        ISystem& system, const SSystemInitParams&)
    {
        AZ_Printf("", "OnCrySystemInitialized");

        SessionEventBus::Handler::BusConnect(
            system.GetINetwork()->GetGridMate());
    }

    void MultiplayerCloseAllNetworkPeersSystemComponent::CreateWorkerEntity()
    {
        m_workerEntity = aznew AZ::Entity("Game Player");
        if (m_workerEntity)
        {
            m_workerEntity->CreateComponent<
                AzFramework::NetBindingComponent>();
            m_workerEntity->CreateComponent<
                CloseNetworkPeersComponent>();
            m_workerEntity->Init();
            m_workerEntity->Activate();

            AZ::EntityBus::MultiHandler::BusConnect(
                m_workerEntity->GetId());
        }

        AZ_Assert(m_workerEntity != nullptr,
            "Could not create worker Entity.");
        AZ_Assert(m_workerEntity->GetState() ==
            AZ::Entity::ES_ACTIVE,
            "Worker entity could not be activated.");
    }
}
