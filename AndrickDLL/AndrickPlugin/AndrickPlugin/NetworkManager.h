#ifndef NETWORK_MANAGER_H_
#define NETWORK_MANAGER_H_

#include "Server.h"
#include "Client.h"

class NetworkManager
{
public:
	NetworkManager() = default;
	~NetworkManager()
	{
		if (currentUser)
		{
			delete currentUser;
			currentUser = nullptr;
		}
	}

	static NetworkManager& get() { static NetworkManager instance; return instance; }

	User* currentUser = nullptr;
};

#endif //NETWORK_MANAGER_H_

#ifndef PLUGIN_NETWORK_H_
#define PLUGIN_NETWORK_H_

//Any file of this type needs to include lib.h
#include "main/lib.h"

// If C++ is being used in the DLL
#ifdef __cplusplus
extern "C"
{
#else

// C code

#endif // End __cplusplus

// Andrick DLL Interface functions
////////////////////////////

ANDRICK_PLUGIN_SYMBOL bool InitServer(const char* username, int port, int maxUserCount);
ANDRICK_PLUGIN_SYMBOL bool InitClient(const char* username, const char* ipAddress, int port);

ANDRICK_PLUGIN_SYMBOL bool StartConnectingToServer();
ANDRICK_PLUGIN_SYMBOL bool DisconnectFromServer();
ANDRICK_PLUGIN_SYMBOL bool ShutdownRakNet();

////////////////////////////

#ifdef __cplusplus // Start __cplusplus
}
#else

// C code

#endif // End __cplusplus

// C++ Mode

#endif // End PLUGIN_NETWORK_H_