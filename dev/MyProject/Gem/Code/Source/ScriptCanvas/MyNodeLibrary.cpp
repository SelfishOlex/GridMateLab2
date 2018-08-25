#include "MyProject_precompiled.h"
#include "MyNodeLibrary.h"
#include <ScriptCanvas/Libraries/Libraries.h>
#include <AzCore/Serialization/EditContext.h>
#include "MyScriptCanvasNode.h"

using namespace ScriptCanvas;

namespace MyProject
{
    namespace Libraries
    {
        void MyNodeLibrary::Reflect(AZ::ReflectContext* reflection)
        {
            AZ::SerializeContext* serializeContext = azrtti_cast<AZ::SerializeContext*>(reflection);
            if (serializeContext)
            {
                serializeContext->Class<MyNodeLibrary, Library::LibraryDefinition>()
                    ->Version(1)
                    ;

                AZ::EditContext* editContext = serializeContext->GetEditContext();
                if (editContext)
                {
                    editContext->Class<MyNodeLibrary>("My Nodes", "")->
                        ClassElement(AZ::Edit::ClassElements::EditorData, "")->
                        Attribute(AZ::Edit::Attributes::Icon, "Editor/Icons/ScriptCanvas/Debug.png")
                        ;
                }
            }
        }

        void MyNodeLibrary::InitNodeRegistry(NodeRegistry& nodeRegistry)
        {
            Library::AddNodeToRegistry<MyNodeLibrary, ScriptCanvas::MyProject::MyScriptCanvasNode>(nodeRegistry);
        }

        AZStd::vector<AZ::ComponentDescriptor*> MyNodeLibrary::GetComponentDescriptors()
        {
            return AZStd::vector<AZ::ComponentDescriptor*>({
                ScriptCanvas::MyProject::MyScriptCanvasNode::CreateDescriptor(),
            });
        }
    }
}
