#include "Client.h"
#include "PacketBank.h"

Client::Client(UserID userID, const std::string username, const std::string& ipAddress, const unsigned short port) :
	User(userID, UserType::CLIENT, username, port), mServerAddressStr(ipAddress), mServerAddress(RakNet::SystemAddress(ipAddress.c_str(), port))
{

}

Client::Client(UserID userID, const std::string username, const RakNet::SystemAddress& ipAddress) :
	User(userID, UserType::CLIENT, username, ipAddress.GetPort()), mServerAddress(ipAddress)
{

}

Client::~Client()
{

}

void Client::processPacket(RakNet::Packet* packet)
{
	switch (packet->data[0])
	{
	case static_cast<int>(PacketID::ID_ANDRICK_NEW_USER_CONNECTED):
		processJustConnectedToServer(reinterpret_cast<ToClient_NewUserConnectedPacket*>(packet));
		break;
	default:
		break;
	}
}

void Client::processJustConnectedToServer(ToClient_NewUserConnectedPacket* incomingPacket)
{
	registerUserID(incomingPacket->mClientID);

	//Client will then send a custom packet with their username.
	ToServer_NewUserRegistrationPacket newRegistrationPacket = ToServer_NewUserRegistrationPacket(mUserID, mUsername);
	sendPacket(reinterpret_cast<char*>(&newRegistrationPacket), sizeof(ToServer_NewUserRegistrationPacket), mServerAddress);
}