#ifndef SERVER_H_
#define SERVER_H_

#include <unordered_map>
#include "Client.h"

class Server : public User
{
public:
	Server(const std::string username = "Server", const unsigned short port = DEFAULT_PORT, int maxUserCount = DEFAULT_MAX_USER_COUNT);
	virtual ~Server();

	virtual void processPacket(RakNet::Packet* packet) override;

private:
	static const int DEFAULT_MAX_USER_COUNT = 10;
	static int nextAvailableID;
	static int generateNextID() { return nextAvailableID++; }

	int mMaxUserCount;
	std::unordered_map<UserID, Client*> mConnectedClients;
	std::unordered_map<UserID, const RakNet::SystemAddress> mClientsPendingToJoin;

	void processNewIncomingConnection(const RakNet::SystemAddress& clientAddress);
	void processNewUserRegistration(struct ToServer_NewUserRegistrationPacket* incomingPacket);
	void updateConnectedClients(const Client& newClient);
};

#endif