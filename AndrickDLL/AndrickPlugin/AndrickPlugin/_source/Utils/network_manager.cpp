#include <_source/Utils/andrick_common.h>
#include <_source/Utils/network_manager.h>

int ActivateServer(int maxUsers)
{
	NetworkManager::get();
	EventSystem::get();

	gNetManager.mpServer = nullptr;
	gNetManager.mpClient = nullptr;
	gNetManager.mpPacketHandler = nullptr;

	return initializeServer(maxUsers);
}

int ActivateClient(char* ip)
{
	NetworkManager::get();
	EventSystem::get();

	gNetManager.mpServer = nullptr;
	gNetManager.mpClient = nullptr;
	gNetManager.mpPacketHandler = nullptr;

	int result = initializeClient(ip);

	gEventSystem.queueNetworkEvent(std::make_shared<ConnectionRequestJoinEvent>(gNetManager.mpClient->getId(), "noob"));

	return result;
}

bool TestMeDaddy()
{
	return true;
}

void UpdateClient()
{
	if (gNetManager.mpPacketHandler && gNetManager.mpPacketHandler->isInitialized())
	{
		gNetManager.mpPacketHandler->processInboundPackets();
	}

	gEventSystem.executeQueuedLocalEvents();

	gEventSystem.sendQueuedNetworkEvents();
}

void UpdateServer()
{
	if (gNetManager.mpPacketHandler && gNetManager.mpPacketHandler->isInitialized())
	{
		gNetManager.mpPacketHandler->processInboundPackets();
	}

	gEventSystem.executeQueuedLocalEvents();

	gEventSystem.sendQueuedNetworkEvents();
}