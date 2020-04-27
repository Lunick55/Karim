#include <_source/Utils/andrick_common.h>
#include <_source/Utils/network_manager.h>

bool ActivateServer(int maxUsers)
{
	NetworkManager::get();
	EventSystem::get();

	gNetManager.mpServer = nullptr;
	gNetManager.mpClient = nullptr;
	gNetManager.mpPacketHandler = nullptr;

	return initializeServer(maxUsers);
}

bool ActivateClient(char* ip, char* username)
{
	NetworkManager::get();
	EventSystem::get();

	gNetManager.mpServer = nullptr;
	gNetManager.mpClient = nullptr;
	gNetManager.mpPacketHandler = nullptr;

	return initializeClient(ip, username);
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

void CreateMessagePacket(char* packet)
{
	std::shared_ptr<MessageEvent> packetData = std::make_shared<MessageEvent>(std::string(packet));
	gEventSystem.queueNetworkEvent(packetData);
}

char* ReadMessageLog()
{
	if (!gNetManager.mpClient)
	{
		return 0;
	}
	if (!gNetManager.mpClient->chatlog.empty())
	{
		//char* message = (char*)gNetManager.mpClient->chatlog.front().c_str();
		char* message = NULL;

		message = (char*)::CoTaskMemAlloc(strlen(gNetManager.mpClient->chatlog.front().c_str() + sizeof(char)));

		strcpy(message, gNetManager.mpClient->chatlog.front().c_str());
		gNetManager.mpClient->chatlog.pop();

		return message;
	}
	return 0;
}

char* GetUsername()
{
	char* name = NULL;

	name = (char*)::CoTaskMemAlloc(strlen(gNetManager.mpClient->getUsername().c_str() + sizeof(char)));

	strcpy(name, gNetManager.mpClient->getUsername().c_str());

	return name;
}

void GetPlayerData(PlayerData& data)
{
	data.ID = gNetManager.mpClient->getId();
	//More if needed
}

int GetConnectedUserCount()
{
	return (int)gNetManager.mpClient->getConnectedUserCount();
}

void GetConnectedUserId(int ids[])
{
	gNetManager.mpClient->getConnectedUserIds(ids);
}

bool DidWeConnectToServer()
{
	return gNetManager.mpPacketHandler && gNetManager.mpPacketHandler->mIsConnected;
}

void DisconnectUser()
{
	gEventSystem.queueNetworkEvent(std::make_shared<UserDisconnectedEvent>(gNetManager.mpClient->getId()));
}

void RequestJoinServer()
{
	//gEventSystem.queueNetworkEvent(std::make_shared<ConnectionRequestJoinEvent>(
	//	gNetManager.mpClient->getId(), gNetManager.mpClient->getUsername()));
}