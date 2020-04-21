#ifndef NETWORK_MANAGER_H_
#define NETWORK_MANAGER_H_

#include <_source/Utils/andrick_common.h>
#include <_source/Networking/andrick_client.h>
#include <_source/Networking/andrick_server.h>
#include <_source/Networking/Packet/andrick_packethandler.h>

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
ANDRICK_PLUGIN_SYMBOL void ActivateServer();
ANDRICK_PLUGIN_SYMBOL bool TestMeDaddy();

#ifdef __cplusplus // Start __cplusplus
}
#else

// C code

#endif // End __cplusplus

// C++ Mode

#endif // End PLUGIN_NETWORK_H_