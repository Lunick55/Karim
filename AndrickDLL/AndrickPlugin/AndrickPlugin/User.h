#ifndef USER_H_
#define USER_H_

#include <string>
#include <RakTits/RakPeerInterface.h>
#include <RakTits/MessageIdentifiers.h>

enum class UserType
{
	UNDEFINED,
	SERVER,
	CLIENT
};

typedef int UserID;

class User
{
public:
	static const int USERNAME_LENGTH = 16;

	User(UserID userID, UserType userType = UserType::UNDEFINED, const std::string username = "Noob0", const unsigned short port = DEFAULT_PORT);
	virtual ~User();

	UserType getUserType() const { return mUserType; }
	const RakNet::SystemAddress& getLocalAddress() const { return mLocalAddress; }
	unsigned short getNumberOfOpenConnections() const { return mpPeer->NumberOfConnections(); }

	bool startRakNet(int maxConnections = 1);
	bool connect(const std::string& ipAddress);
	bool disconnect();
	bool stopRakNet();

	virtual int readPackets() final;
	virtual void processPacket(RakNet::Packet* packet) = 0;

	bool sendPacket(const char* packetData, std::size_t packetSize, const RakNet::SystemAddress& ipAddress) const;

protected:
	static const unsigned short DEFAULT_PORT = 5555;

	UserID mUserID;
	UserType mUserType = UserType::UNDEFINED;
	std::string mUsername;
	unsigned short mPort = DEFAULT_PORT;

	RakNet::RakPeerInterface* mpPeer = nullptr;
	RakNet::SystemAddress mLocalAddress;
	RakNet::SocketDescriptor mSocketDescriptor;

	void registerUserID(UserID userID) { mUserID = userID; };
};

#endif