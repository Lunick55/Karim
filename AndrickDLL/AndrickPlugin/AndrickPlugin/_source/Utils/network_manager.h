#ifndef NETWORK_MANAGER_H_
#define NETWORK_MANAGER_H_

#include <_source/Utils/andrick_common.h>
#include <string>
#include <_source/Networking/andrick_client.h>
#include <_source/Networking/andrick_server.h>
#include <_source/Networking/Packet/andrick_packethandler.h>

#pragma pack(push, 1)
struct Cummies
{
	int numCummies = 0;
	bool cumFriend = false;
	float cumPercent = 0.5f;
	//char* cumName;
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

	struct Cummies cum;

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
ANDRICK_PLUGIN_SYMBOL int ActivateServer(int maxUsers);
ANDRICK_PLUGIN_SYMBOL int ActivateClient(char* ip);

//Networking
ANDRICK_PLUGIN_SYMBOL int ShutdownNetwork();
ANDRICK_PLUGIN_SYMBOL void ProcessPackets();
ANDRICK_PLUGIN_SYMBOL void ExecuteEvents();
ANDRICK_PLUGIN_SYMBOL void SendPackets();
ANDRICK_PLUGIN_SYMBOL void CreatePacket(char* packet);

//Testing //daddy is dll
ANDRICK_PLUGIN_SYMBOL Cummies FromDaddy();
ANDRICK_PLUGIN_SYMBOL void ToDaddy(Cummies incuming);

#ifdef __cplusplus // Start __cplusplus
}
#else

// C code

#endif // End __cplusplus

// C++ Mode

#endif // End PLUGIN_NETWORK_H_