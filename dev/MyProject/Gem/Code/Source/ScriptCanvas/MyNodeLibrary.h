#pragma once

#include <ScriptCanvas/Libraries/Libraries.h>

namespace MyProject
{
    namespace Libraries
    {
        struct MyNodeLibrary : public ScriptCanvas::Library::LibraryDefinition
        {
            AZ_RTTI(MyNodeLibrary, "{55c3e827-0048-4f65-a461-692177c25699}", ScriptCanvas::Library::LibraryDefinition);

            static void Reflect(AZ::ReflectContext*);
            static void InitNodeRegistry(ScriptCanvas::NodeRegistry& nodeRegistry);
            AZStd::vector<AZ::ComponentDescriptor*> GetComponentDescriptors();
        };
    }
}
