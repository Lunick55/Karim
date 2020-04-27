#include "NetworkManager.h"

bool InitServer(const char* username, int port, int maxUserCount)
{
	bool success = false;
	NetworkManager& Instance = NetworkManager::get();

	if (!Instance.currentUser)
	{
		Instance.currentUser = new Server(std::string(username), static_cast<unsigned short>(port), maxUserCount);
		success = Instance.currentUser->startRakNet(maxUserCount);
	}

	return success;
}

bool InitClient(const char* username, const char* ipAddress, int port)
{
	bool success = false;
	NetworkManager& Instance = NetworkManager::get();

	if (!Instance.currentUser)
	{
		Instance.currentUser = new Client(Client::UNDEFINED_ID, std::string(username), std::string(ipAddress), static_cast<unsigned short>(port));
		success = Instance.currentUser->startRakNet();
	}

	return success;
}

bool StartConnectingToServer()
{
	bool success = true;
	NetworkManager& Instance = NetworkManager::get();

	if (Instance.currentUser)
	{
		Client* client = static_cast<Client*>(Instance.currentUser);
		success = client->connect(client->getServerAddress().ToString());
	}

	return success;
}

bool DisconnectFromServer()
{
	bool success = true;
	NetworkManager& Instance = NetworkManager::get();

	if (Instance.currentUser)
	{
		Client* client = static_cast<Client*>(Instance.currentUser);
		success = client->disconnect();
	}

	return success;
}

bool ShutdownRakNet()
{
	bool success = false;
	NetworkManager& Instance = NetworkManager::get();

	if (Instance.currentUser)
		success = Instance.currentUser->stopRakNet();

	return success;
}