#include "MultiplayerCloseAllNetworkPeers_precompiled.h"
#include "WorkerComponent.h"
#include <AzCore/Serialization/EditContext.h>
#include <GridMate/Replica/ReplicaFunctions.h>
#include "MultiplayerCloseAllNetworkPeers/ShutdownApplication.h"

using namespace AZ;
using namespace MultiplayerCloseAllNetworkPeers;
using namespace GridMate;

class WorkerComponent::Chunk
    : public GridMate::ReplicaChunk
{
public:
    GM_CLASS_ALLOCATOR(Chunk);

    Chunk() : m_closeAllRpc("CloseAllRpc") {}

    bool IsReplicaMigratable() override { return true; }

    static const char* GetChunkName()
    {
        return "WorkerComponent::Chunk";
    }

    GridMate::Rpc<>::BindInterface<
        WorkerComponent,
        &WorkerComponent::OnCloseAll> m_closeAllRpc;
};

void WorkerComponent::Reflect(
    AZ::ReflectContext* context)
{
    if (auto sc = azrtti_cast<AZ::SerializeContext*>(context))
    {
        sc->Class<WorkerComponent, AZ::Component>()
            ->Version(1);

        if (auto ec = sc->GetEditContext())
        {
            ec->Class<WorkerComponent>(
                "Close All Network Peers",
                "[Closes the clients and the server]")
                ->ClassElement(
                    Edit::ClassElements::EditorData, "")
                ->Attribute(Edit::Attributes::Category,
                    "Testing Tools")
                ->Attribute(Edit::Attributes::
                    AppearsInAddComponentMenu,
                    AZ_CRC("Game"));
        }
    }

    auto& descTable = ReplicaChunkDescriptorTable::Get();
    if (!descTable.FindReplicaChunkDescriptor(
        ReplicaChunkClassId(Chunk::GetChunkName())))
    {
        descTable.RegisterChunkType<Chunk>();
    }
}

void WorkerComponent::GetProvidedServices(
    AZ::ComponentDescriptor::DependencyArrayType& list)
{
    list.push_back(AZ_CRC("CloseNetworkPeersService"));
}

void WorkerComponent::GetIncompatibleServices(
    AZ::ComponentDescriptor::DependencyArrayType& list)
{
}

void WorkerComponent::GetRequiredServices(
    AZ::ComponentDescriptor::DependencyArrayType& list)
{
}

void WorkerComponent::GetDependentServices(
    AZ::ComponentDescriptor::DependencyArrayType& list)
{
}

void WorkerComponent::Activate()
{
    m_isShuttinDown = false;

    CloseAllRequestBus::Handler::BusConnect();
    TickBus::Handler::BusConnect();
}

void WorkerComponent::Deactivate()
{
    CloseAllRequestBus::Handler::BusDisconnect();
    TickBus::Handler::BusDisconnect();

    m_isShuttinDown = false;
}

void WorkerComponent::CloseAll()
{
    if (auto chunk = static_cast<Chunk*>(m_chunk.get()))
    {
        chunk->m_closeAllRpc();
    }
    else
    {
        ShutdownApplication();
    }
}

bool WorkerComponent::OnCloseAll(
    const GridMate::RpcContext& /*rc*/)
{
    m_shutdownCountdown = m_ticksBeforeShutdown;
    m_isShuttinDown = true;
    return true;
}

void WorkerComponent::OnTick(float, ScriptTimePoint)
{
    if (m_isShuttinDown && m_shutdownCountdown-- == 0)
    {
        MultiplayerCloseAllNetworkPeers::ShutdownApplication();
    }
}

GridMate::ReplicaChunkPtr
WorkerComponent::GetNetworkBinding()
{
    m_chunk = GridMate::CreateReplicaChunk<Chunk>();
    m_chunk->SetHandler(this);
    return m_chunk;
}

void WorkerComponent::SetNetworkBinding(
    GridMate::ReplicaChunkPtr chunk)
{
    m_chunk = chunk;
    m_chunk->SetHandler(this);
}

void WorkerComponent::UnbindFromNetwork()
{
    m_chunk->SetHandler(nullptr);
    m_chunk = nullptr;
}
