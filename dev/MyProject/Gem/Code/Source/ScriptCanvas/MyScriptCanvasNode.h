#pragma once

#include <ScriptCanvas/Core/Node.h>
#include <ScriptCanvas/Core/Graph.h>

#include <ScriptCanvas/CodeGen/CodeGen.h>

#include <AzCore/Component/TickBus.h>

#include <Source/ScriptCanvas/MyScriptCanvasNode.generated.h>

#include <AzCore/RTTI/TypeInfo.h>

namespace ScriptCanvas {
namespace MyProject
{
    class MyScriptCanvasNode
        : public ScriptCanvas::Node
        , AZ::TickBus::Handler
    {
        ScriptCanvas_Node(MyScriptCanvasNode,
            ScriptCanvas_Node::Name("My ScriptCanvas Node")
            ScriptCanvas_Node::Uuid("{0AED9EC4-E05B-4FAE-B9B5-27933F633F0D}")
            ScriptCanvas_Node::Description("My first node")
        );

    public:

        MyScriptCanvasNode();

    protected:

        // Inputs
        ScriptCanvas_In(ScriptCanvas_In::Name("In", "in")
                        ScriptCanvas_In::Contracts({ DisallowReentrantExecutionContract }));

        // Outputs
        ScriptCanvas_Out(ScriptCanvas_Out::Name("Out", "out"));

        void OnInputSignal(const ScriptCanvas::SlotId&) override;
        void OnDeactivate() override;
        void OnTick(float deltaTime, AZ::ScriptTimePoint time) override;
    };
} }
