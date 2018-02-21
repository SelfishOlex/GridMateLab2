
#pragma once

#include <AzCore/Component/Component.h>

#include <MultiplayerCloseAllNetworkPeers/MultiplayerCloseAllNetworkPeersBus.h>
#include <AzCore/Component/EntityBus.h>
#include <AzFramework/Entity/GameEntityContextBus.h>
#include <GridMate/Session/Session.h>
#include <CrySystemBus.h>

namespace MultiplayerCloseAllNetworkPeers
{
    class MultiplayerCloseAllNetworkPeersSystemComponent
        : public AZ::Component
        , protected MultiplayerCloseAllNetworkPeersRequestBus::Handler
        , public AZ::EntityBus::MultiHandler
        , AzFramework::GameEntityContextEventBus::Handler
        , public GridMate::SessionEventBus::Handler
        , public CrySystemEventBus::Handler
    {
    public:
        AZ_COMPONENT(MultiplayerCloseAllNetworkPeersSystemComponent, "{30168C7B-5DCE-4404-83DC-6349CB07A60F}");

        static void Reflect(AZ::ReflectContext* context);

        static void GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided);
        static void GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required);
        static void GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompat);
        static void GetDependentServices(AZ::ComponentDescriptor::DependencyArrayType& dependent);

    protected:
        // CloseAllNetworkPeersRequestBus interface implementation
        void CloseAllNetworkPeers() override;

        // AZ::Component interface implementation
        void Activate() override;
        void Deactivate() override;

        // GameEntityContextEventBus
        void OnGameEntitiesStarted() override;
        void OnGameEntitiesReset() override;

        // SessionEventBus
        void OnSessionHosted(
            GridMate::GridSession* session) override;
        void OnSessionDelete(GridMate::GridSession* session) override;
        void OnSessionEnd(GridMate::GridSession* session) override;

        // CrySystemEventBus
        void OnCrySystemInitialized(ISystem&,
            const SSystemInitParams&) override;

        void CreateWorkerEntity();

    private:
        AZ::Entity* m_workerEntity = nullptr;
        bool m_isHost = false;
        bool m_isMapLoaded = false;
    };
}
