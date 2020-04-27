#include "User.h"

User::User(UserID userID, UserType userType, const std::string username, unsigned short int port) :
	mUserType(userType), mUsername(username), mPort(port)
{

}

User::~User()
{

}

bool User::startRakNet(int maxConnections)
{
	bool success = false;
	if (!mpPeer) mpPeer = RakNet::RakPeerInterface::GetInstance();

	if (mpPeer)
	{
		if (mUserType == UserType::SERVER)
			mSocketDescriptor = RakNet::SocketDescriptor(mPort, 0);

		if (mpPeer->Startup(maxConnections, &mSocketDescriptor, 1) == RakNet::StartupResult::RAKNET_STARTED)
		{
			mpPeer->SetMaximumIncomingConnections(maxConnections);
			mpPeer->SetOccasionalPing(true);
			mLocalAddress = mpPeer->GetSystemAddressFromGuid(mpPeer->GetMyGUID());
			success = true;
		}
	}

	return success;
}

bool User::connect(const std::string& ipAddress)
{
	bool success = false;

	if (mpPeer)
	{
		RakNet::ConnectionAttemptResult result = mpPeer->Connect(ipAddress.c_str(), mPort, 0, 0);
		success = (result == RakNet::ConnectionAttemptResult::CONNECTION_ATTEMPT_STARTED);
	}

	return success;
}

bool User::disconnect()
{
	bool success = false;

	if (mpPeer)
	{
		const unsigned short OPEN_CONNECTION_COUNT = getNumberOfOpenConnections();
		for (unsigned short i = 0; i < OPEN_CONNECTION_COUNT; ++i)
			mpPeer->CloseConnection(mpPeer->GetSystemAddressFromIndex(i), true);

		success = true;
	}

	return success;
}

bool User::stopRakNet()
{
	bool success = false;

	if (mpPeer)
	{
		disconnect();
		mpPeer->Shutdown(500);
		RakNet::RakPeerInterface::DestroyInstance(mpPeer);
		mpPeer = nullptr;
		success = true;
	}

	return success;
}

int User::readPackets()
{
	RakNet::Packet* incomingPacket;
	int packetsProcessed = 0;

	for (incomingPacket = mpPeer->Receive(); 
		incomingPacket != nullptr; mpPeer->DeallocatePacket(incomingPacket), 
		incomingPacket = mpPeer->Receive(), ++packetsProcessed)
	{
		processPacket(incomingPacket);
	}

	return packetsProcessed;
}

bool User::sendPacket(const char* packetData, std::size_t packetSize, const RakNet::SystemAddress& ipAddress) const
{
	bool isBroadcast = (ipAddress == RakNet::UNASSIGNED_SYSTEM_ADDRESS);

	int success = mpPeer->Send(packetData, static_cast<int>(packetSize), PacketPriority::IMMEDIATE_PRIORITY, 
		PacketReliability::RELIABLE_ORDERED, 0, ipAddress, isBroadcast);

	return success > 0;
}