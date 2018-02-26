#pragma once

struct IConsoleCmdArgs;

namespace WindowPosition
{
    class WindowPositionCommands
    {
    public:
        void Register();
        void Unregister();

        static void WindowX(IConsoleCmdArgs* args);
        static void WindowY(IConsoleCmdArgs* args);
        static void WindowXY(IConsoleCmdArgs* args);
    };
}
