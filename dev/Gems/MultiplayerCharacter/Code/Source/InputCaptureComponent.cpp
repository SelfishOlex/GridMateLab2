#include "MultiplayerCharacter_precompiled.h"
#include "InputCaptureComponent.h"
#include <AzCore/Serialization/EditContext.h>
#include <MultiplayerCharacter/PlayerControlsRequestBus.h>
#include <AzFramework/Input/Devices/Keyboard/InputDeviceKeyboard.h>

using namespace AzFramework;
using namespace MultiplayerCharacter;

void InputCaptureComponent::Activate()
{
    // Connect to receive input events
    InputChannelEventListener::Connect();
}

void InputCaptureComponent::Deactivate()
{
    // Disconnect as a good practice
    InputChannelEventListener::Disconnect();
}

void InputCaptureComponent::Reflect(AZ::ReflectContext* ref)
{
    auto sc = azrtti_cast<AZ::SerializeContext*>(ref);
    if (!sc) return;

    sc->Class<InputCaptureComponent, Component>()
        ->Version(1);

    AZ::EditContext* ec = sc->GetEditContext();
    if (!ec) return;

    using namespace AZ::Edit::Attributes;
    // reflection of this component for Lumberyard Editor
    ec->Class<InputCaptureComponent>("Player Input Capture",
        "[Captures input the C++ way]")
      ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
        ->Attribute(AppearsInAddComponentMenu,
            AZ_CRC("Game", 0x232b318c))
        ->Attribute(Category, "Multiplayer Character");
}

void InputCaptureComponent::GetProvidedServices(
    AZ::ComponentDescriptor::DependencyArrayType& prov)
{
    prov.push_back(AZ_CRC("InputCaptureService"));
}

bool InputCaptureComponent::OnInputChannelEventFiltered(
    const AzFramework::InputChannel& inputChannel)
{
    const AzFramework::InputDeviceId deviceId =
        inputChannel.GetInputDevice().GetInputDeviceId();

    if (deviceId == AzFramework::InputDeviceKeyboard::Id)
        return OnKeyboardEvent(inputChannel);

    return false; // key not consumed
}

bool InputCaptureComponent::OnKeyboardEvent(
    const InputChannel& inputChannel)
{
    const InputChannelId inputType = inputChannel.
        GetInputChannelId();

    if (inputType == InputDeviceKeyboard::Key::AlphanumericW)
    {
        const bool pressed = !!inputChannel.GetValue();
        CheckAndUpdateForward(pressed);
        return true; // key consumed
    }
    return false; // key not consumed
}

void InputCaptureComponent::CheckAndUpdateForward(bool pressed)
{
    if (m_isForwardPressed == pressed) return;

    PlayerControlsRequestBus::Broadcast(
        &PlayerControlsRequestBus::Events::MoveForward,
        pressed ? ActionState::Started : ActionState::Stopped);

    m_isForwardPressed = pressed;
}
