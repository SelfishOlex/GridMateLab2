#include "MyProject_precompiled.h"
#include "MyScriptHelperComponent.h"
#include <AzCore/Serialization/EditContext.h>
#include <AzCore/RTTI/BehaviorContext.h>
#include <AzFramework/Network/NetBindingHandlerBus.h>

using namespace MyProject;

void MyScriptHelperComponent::Reflect(AZ::ReflectContext* rc)
{
    using namespace AZ;
    if (auto sc = azrtti_cast<SerializeContext*>(rc))
    {
        sc->Class<MyScriptHelperComponent, Component>()
            ->Version(1);
        using namespace AZ::Edit::Attributes;
        using namespace AZ::Edit::ClassElements;
        if (auto editContext = sc->GetEditContext())
        {
            editContext->Class<MyScriptHelperComponent>(
                "MyScriptHelperComponent", "[script helper]")
               ->ClassElement(EditorData, "")
               ->Attribute(Category, "PrototypingBase")
               ->Attribute(AppearsInAddComponentMenu,
                   AZ_CRC("Game", 0x232b318c));
        }
    }

    auto* bc = azrtti_cast<AZ::BehaviorContext*>(rc);
    if(!bc) return;
    bc->Class<MyHelper>("MyHelper")->
        Method("IsServer", &MyHelper::IsEntityAuthoritative)->
        Method("IsClient",
            [](AZ::EntityId entity)
            {
                return !MyHelper::IsEntityAuthoritative(entity);
            })
    ;
}

bool MyHelper::IsEntityAuthoritative(AZ::EntityId entity)
{
    return AzFramework::NetQuery::IsEntityAuthoritative(entity);
}
