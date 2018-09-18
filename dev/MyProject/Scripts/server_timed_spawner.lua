-- server_timed_spawner.lua --
local ServerTimedSpawner = {}

function ServerTimedSpawner:OnActivate()
    if MyHelper.IsServer(self.entityId) then
        Debug.Log("Spawner enabled")
        RandomTimedSpawnerRequestBus.Event.Enable(self.entityId)
    end
end

return ServerTimedSpawner