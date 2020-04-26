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

int ShutdownNetwork()
{
	return shutdownRakNet();
}

void ProcessPackets()
{
	if (gNetManager.mpPacketHandler && gNetManager.mpPacketHandler->isInitialized())
	{
		gNetManager.mpPacketHandler->processInboundPackets();
	}
}

void ExecuteEvents()
{
	gEventSystem.executeQueuedLocalEvents();
}

void SendPackets()
{
	gEventSystem.sendQueuedNetworkEvents();
}

void CreatePacket(char* packet)
{
	//ConnectionRequestAcceptedPacket* requestAcceptedPacket = (ConnectionRequestAcceptedPacket*)packet->data;
	//newEvents.push_back(std::make_shared<ConnectionRequestAcceptedEvent>(packet->systemAddress, requestAcceptedPacket->newUserId));
	//send it out
}


//Testing
Cummies FromDaddy()
{
	return gNetManager.cum;
}

void ToDaddy(Cummies incuming)
{
	NetworkManager::get();
	EventSystem::get();

	gNetManager.cum = (incuming);	
}