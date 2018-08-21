-- Orbiting.lua -- Constant rotation around Z axis
local Orbiting =
{
    Properties =
    {
        -- Property definitions
        speed = { default = 10,
            description = "speed of orbiting",
            suffix = "deg/sec" }
    }
}

function Orbiting:OnActivate()
    -- Activation Code
    Debug.Log("Is this editor? " .. tostring(MyHelperBus.Broadcast.IsEditor()))
    if MyHelper.IsServer(self.entityId) then
        Debug.Log("Orbiting activated")
        self.tickHandler = TickBus.Connect(self)
    end
end

function Orbiting:OnDeactivate()
    -- Deactivation Code
    if self.tickHandler ~= nil then
        self.tickHandler:Disconnect()
    end
end

function Orbiting:OnTick(deltaTime, timePoint)
    TransformBus.Event.RotateAroundLocalZ(
        self.entityId, self.Properties.speed*deltaTime)
end

return Orbiting