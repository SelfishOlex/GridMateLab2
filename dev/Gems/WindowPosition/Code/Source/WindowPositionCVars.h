#pragma once

struct IConsoleCmdArgs;

namespace WindowPosition
{
    class WindowPositionCVars
    {
    public:
        void RegisterCVars();
        void UnregisterCVars();

        static void WindowX(IConsoleCmdArgs* args);
        static void WindowY(IConsoleCmdArgs* args);
        static void WindowXY(IConsoleCmdArgs* args);
    };
}
