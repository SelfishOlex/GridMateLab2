#include "MyProject_precompiled.h"
#include "MyUICanvasLoaderComponent.h"
#include <AzCore/Serialization/EditContext.h>
#include <LyShine/Bus/World/UiCanvasRefBus.h>

using namespace MyProject;

void MyUICanvasLoaderComponent::Activate()
{
#if !defined(DEDICATED_SERVER)
    UiCanvasAssetRefBus::Event(GetEntityId(),
        &UiCanvasAssetRefBus::Events::LoadCanvas);
#endif
}

void MyUICanvasLoaderComponent::GetRequiredServices(
    AZ::ComponentDescriptor::DependencyArrayType& prov)
{
    prov.push_back(AZ_CRC("UiCanvasRefService"));
}

void MyUICanvasLoaderComponent::Reflect(AZ::ReflectContext* rc)
{
    auto sc = azrtti_cast<AZ::SerializeContext*>(rc);
    if (!sc) return;

    sc->Class<MyUICanvasLoaderComponent, Component>()->Version(1);

    AZ::EditContext* ec = sc->GetEditContext();
    if (!ec) return;

    using namespace AZ::Edit::Attributes;
    // reflection of this component for Lumberyard Editor
    ec->Class<MyUICanvasLoaderComponent>("My UI Canvas Loader",
        "[Loads UI canvas on clients only]")
      ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
        ->Attribute(AppearsInAddComponentMenu, AZ_CRC("Game"))
        ->Attribute(Category, "My Project");
}
