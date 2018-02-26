#include "WindowPosition_precompiled.h"
#include "WindowPositionCommands.h"
#include <windows.h>
#include <Winuser.h>
#include <ISystem.h>
#include <IConsole.h>
#include "AzCore/std/string/conversions.h"

using namespace WindowPosition;

void WindowPositionCommands::Register()
{
    ISystem* system = nullptr;
    CrySystemRequestBus::BroadcastResult(system, &CrySystemRequestBus::Events::GetCrySystem);
    if (system)
    {
        IConsole* console = system->GetIConsole();
        if (console)
        {
            console->AddCommand("windowx", WindowX, 0,
                "set X position of the window");
            console->AddCommand("windowy", WindowY, 0,
                "set Y position of the window");
            console->AddCommand("windowxy", WindowXY, 0,
                "set X and Y position of the window");
        }
    }
}

void WindowPositionCommands::Unregister()
{
    ISystem* system = nullptr;
    CrySystemRequestBus::BroadcastResult(system, &CrySystemRequestBus::Events::GetCrySystem);
    if (system)
    {
        IConsole* console = system->GetIConsole();
        if (console)
        {
            console->RemoveCommand("windowx");
            console->RemoveCommand("windowy");
            console->RemoveCommand("windowxy");
        }
    }
}

void WindowPositionCommands::WindowX(IConsoleCmdArgs* args)
{
    if (args->GetArgCount() > 1)
    {
        const int x = AZStd::stoi(AZStd::string(args->GetArg(1)));

        if (const HWND windowHandle = GetActiveWindow())
        {
            WINDOWINFO windowInfo;
            windowInfo.cbSize = sizeof(WINDOWINFO);
            if (GetWindowInfo(windowHandle, &windowInfo))
                SetWindowPos(windowHandle, nullptr,
                    x,
                    windowInfo.rcWindow.top,
                    0, 0, SWP_NOOWNERZORDER | SWP_NOSIZE);
        }
    }
}

void WindowPositionCommands::WindowY(IConsoleCmdArgs* args)
{
    if (args->GetArgCount() > 1)
    {
        const int y = AZStd::stoi(AZStd::string(args->GetArg(1)));

        if (const HWND windowHandle = GetActiveWindow())
        {
            WINDOWINFO windowInfo;
            windowInfo.cbSize = sizeof(WINDOWINFO);
            if (GetWindowInfo(windowHandle, &windowInfo))
                SetWindowPos(windowHandle, nullptr,
                    windowInfo.rcWindow.left,
                    y,
                    0, 0, SWP_NOOWNERZORDER | SWP_NOSIZE);
        }
    }
}

void WindowPositionCommands::WindowXY(IConsoleCmdArgs* args)
{
    if (args->GetArgCount() > 2)
    {
        const int x = AZStd::stoi(AZStd::string(args->GetArg(1)));
        const int y = AZStd::stoi(AZStd::string(args->GetArg(2)));

        if (const HWND windowHandle = GetActiveWindow())
            SetWindowPos(windowHandle, nullptr,
                x,
                y,
                0, 0, SWP_NOOWNERZORDER | SWP_NOSIZE);
    }
}
