#ifndef PACKET_BANK_H_
#define PACKET_BANK_H_

#include <RakTits/RakPeerInterface.h>
#include <RakTits/MessageIdentifiers.h>
#include "User.h"

typedef int UserID;

enum class PacketID : unsigned char
{
	ID_ANDRICK_NEW_USER_CONNECTED = ID_USER_PACKET_ENUM,
	ID_ANDRICK_NEW_USER_REGISTRATION
};

//When a new user just connects, the server sends the new client this packet to tell them their ID.
#pragma pack(push, 1)
struct ToClient_NewUserConnectedPacket
{
	PacketID mPacketID;
	UserID mClientID;
	ToClient_NewUserConnectedPacket(UserID clientID) :
		mPacketID(PacketID::ID_ANDRICK_NEW_USER_CONNECTED), mClientID(clientID) {}

};
#pragma pack(pop)

//After the user receives a ToClient_NewUserConnectedPacket, the user sends this registration packet
//back to the server to fully complete the connection.
#pragma pack(push, 1)
struct ToServer_NewUserRegistrationPacket
{
	PacketID mPacketID;
	UserID mClientID;
	char mUsername[User::USERNAME_LENGTH];
	ToServer_NewUserRegistrationPacket(UserID clientID, const std::string& username) :
		mPacketID(PacketID::ID_ANDRICK_NEW_USER_REGISTRATION), mClientID(clientID)
	{ strcpy(mUsername, username.c_str()); }
};
#pragma pack(pop)

#endif