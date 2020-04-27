#include "Server.h"
#include "PacketBank.h"

int Server::nextAvailableID = 0;

Server::Server(const std::string username, const unsigned short port, int maxUserCount) :
	User(generateNextID(), UserType::SERVER, username, port), mMaxUserCount(maxUserCount)
{

}

Server::~Server()
{

}

void Server::processPacket(RakNet::Packet* packet)
{
	switch (packet->data[0])
	{
		case ID_NEW_INCOMING_CONNECTION:
			processNewIncomingConnection(packet->systemAddress);
			break;
		case ID_DISCONNECTION_NOTIFICATION:
			break;
		case ID_CONNECTION_LOST:
			break;
		case static_cast<int>(PacketID::ID_ANDRICK_NEW_USER_REGISTRATION):
			break;
		default:
			break;
	}
}

void Server::processNewIncomingConnection(const RakNet::SystemAddress& clientAddress)
{
	int newUserID = generateNextID();
	//Add the client to a pending list while they are still getting fully initialized.
	mClientsPendingToJoin.insert({ newUserID, clientAddress });

	//Send packet to client saying they can join and give them their unique ID.
	ToClient_NewUserConnectedPacket newConnectionPacket = ToClient_NewUserConnectedPacket(newUserID);
	sendPacket(reinterpret_cast<char*>(&newConnectionPacket), sizeof(ToClient_NewUserConnectedPacket), clientAddress);

	//Client will then send a custom packet with their username.
	//Server will then send a packet with all of the connected client info to the new user.
	//Server will then send the new user's info to all of the currently connected users.
}

void Server::processNewUserRegistration(struct ToServer_NewUserRegistrationPacket* incomingPacket)
{
	auto iter = mClientsPendingToJoin.find(incomingPacket->mClientID);

	if (iter != mClientsPendingToJoin.end())
	{
		Client* newClient = new Client(incomingPacket->mClientID, incomingPacket->mUsername, iter->second);
		mConnectedClients.insert({ incomingPacket->mClientID, newClient });

		//Remove the new client from the pending join list.
		mClientsPendingToJoin.erase(incomingPacket->mClientID);

		//Broad packet to all other connected users.
		updateConnectedClients(*newClient);
	}
}

void Server::updateConnectedClients(const Client& newClient)
{

}