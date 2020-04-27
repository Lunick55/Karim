#ifndef CLIENT_H_
#define CLIENT_H_

#include "User.h"

class Client : public User
{
public:
	static const UserID UNDEFINED_ID = -1;

	Client(UserID userID = UNDEFINED_ID, const std::string username = "Noob0", const std::string& ipAddress = "127.0.0.1", const unsigned short port = DEFAULT_PORT);
	Client(UserID userID = UNDEFINED_ID, const std::string username = "Noob0", const RakNet::SystemAddress& ipAddress = RakNet::UNASSIGNED_SYSTEM_ADDRESS);
	virtual ~Client();

	const std::string& getServerAddressStr() const { return mServerAddressStr; }
	const RakNet::SystemAddress& getServerAddress() const { return mServerAddress; }

	virtual void processPacket(RakNet::Packet* packet) override;

private:
	std::string mServerAddressStr;
	RakNet::SystemAddress mServerAddress;

	void processJustConnectedToServer(struct ToClient_NewUserConnectedPacket* incomingPacket);
};

#endif