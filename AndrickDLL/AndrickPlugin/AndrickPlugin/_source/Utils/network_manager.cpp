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
	if (gNetManager.mpPacketHandler && gNetManager.mpPacketHandler->isInitialized())
	{
		gEventSystem.executeQueuedLocalEvents();
	}
}

void SendPackets()
{
	if (gNetManager.mpPacketHandler && gNetManager.mpPacketHandler->isInitialized())
	{
		gEventSystem.sendQueuedNetworkEvents();
	}
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

void GetConnectedUserIds(int ids[])
{
	gNetManager.mpClient->getConnectedUserIds(ids);
}

bool DidWeInitiallyConnectToServer()
{
	return gNetManager.mpPacketHandler->mIsConnected;
}

int DidServerAcceptOurConnection(int& result)
{
	result = 0;
	if (gNetManager.mpPacketHandler)
		result = gNetManager.mpPacketHandler->mServerAcceptsMe;

	return result;
}

void DisconnectUser()
{
	gEventSystem.queueNetworkEvent(std::make_shared<UserDisconnectedEvent>(gNetManager.mpClient->getId()));
}

int GetMaxUserCount()
{
	return (int)gNetManager.mpPacketHandler->getMaxConnections();
}

void GetUsernames(char* Usernames, int MaxLength)
{
	//Max length is max connections * max length for username
	auto clientMap = gNetManager.mpServer->getConnectedUsers();
	for (int i = 0; i < clientMap.size(); ++i)
	{
		std::string username = clientMap.at(i)->getUsername();
		for (int j = 0; j < username.size(); ++j)
		{
			int index = i * sMAX_USERNAME_LENGTH + j;
			if (MaxLength > index)
			{
				Usernames[(i * sMAX_USERNAME_LENGTH) + j] = username[j];
			}
		}
		Usernames[(i * sMAX_MESSAGE_LENGTH) + (int)username.length()] = '\0';
	}
}