#ifndef NETWORK_MANAGER_H_
#define NETWORK_MANAGER_H_

#include <_source/Utils/andrick_common.h>
#include <string>
#include <_source/Networking/andrick_client.h>
#include <_source/Networking/andrick_server.h>
#include <_source/Networking/Packet/andrick_packethandler.h>

#pragma pack(push, 1)
struct PlayerData
{
public:
	int ID;
};
#pragma pack(pop)

class NetworkManager
{
public:
	NetworkManager() {};
	~NetworkManager() = default;

	static NetworkManager& get()
	{
		static NetworkManager instance;
		return instance;
	}

	std::shared_ptr<class Client> mpClient;
	std::shared_ptr<class Server> mpServer;
	std::shared_ptr<class PacketHandler> mpPacketHandler;

private:
};

#endif //NETWORK_MANAGER_H_

#ifndef PLUGIN_NETWORK_H_
#define PLUGIN_NETWORK_H_

//Any file of this type needs to include lib.h
#include "../../main/lib.h"

// If C++ is being used in the DLL
#ifdef __cplusplus
extern "C"
{
#else

// C code

#endif // End __cplusplus

// C++ code exposed to user program.
ANDRICK_PLUGIN_SYMBOL bool ActivateServer(int maxUsers);
ANDRICK_PLUGIN_SYMBOL bool ActivateClient(char* ip, char* username);
ANDRICK_PLUGIN_SYMBOL bool DidWeInitiallyConnectToServer();
ANDRICK_PLUGIN_SYMBOL int DidServerAcceptOurConnection(int& result);

ANDRICK_PLUGIN_SYMBOL void DisconnectUser();
ANDRICK_PLUGIN_SYMBOL void RequestJoinServer();

//Networking
ANDRICK_PLUGIN_SYMBOL int ShutdownNetwork();
ANDRICK_PLUGIN_SYMBOL void ProcessPackets();
ANDRICK_PLUGIN_SYMBOL void ExecuteEvents();
ANDRICK_PLUGIN_SYMBOL void SendPackets();
ANDRICK_PLUGIN_SYMBOL void CreatePacket(char* packet);
ANDRICK_PLUGIN_SYMBOL void CreateMessagePacket(char* packet);
ANDRICK_PLUGIN_SYMBOL char* ReadMessageLog();
ANDRICK_PLUGIN_SYMBOL char* GetUsername();
ANDRICK_PLUGIN_SYMBOL void GetPlayerData(PlayerData& data);
ANDRICK_PLUGIN_SYMBOL int GetConnectedUserCount();
ANDRICK_PLUGIN_SYMBOL void GetConnectedUserIds(int ids[]);

#ifdef __cplusplus // Start __cplusplus
}
#else

// C code

#endif // End __cplusplus

// C++ Mode

#endif // End PLUGIN_NETWORK_H_