//TODO: Hey andy, this gets mad at all the strcpy, cause it's unsafe. Do we wanna move to srtcpy_s? Or just _CRT_SECURE_NO_WARNINGS to force compile? 

#ifndef PACKET_H_
#define PACKET_H_

#include <_source/Utils/andrick_common.h>
#include <chrono>

#pragma pack(push, 1)
struct ConnectionRequestAcceptedPacket
{
	PacketEventId packetId;
	UserId newUserId;

	ConnectionRequestAcceptedPacket(UserId userId) :
		packetId(andrick_ID_CONNECTION_REQUEST_ACCEPTED),
		newUserId(userId)
	{}
};
#pragma pack(pop)

#pragma pack(push, 1)
struct ConnectionRequestFailedPacket
{
	PacketEventId packetId;
	char errorMessage[sMAX_MESSAGE_LENGTH];

	ConnectionRequestFailedPacket(const std::string& message) :
		packetId(andrick_ID_CONNECTION_ATTEMPT_FAILED)
	{
		strcpy(errorMessage, message.c_str());
	}
};
#pragma pack(pop)

//Client sends to server to join.
#pragma pack(push, 1)
struct RequestJoinServerPacket
{
	PacketEventId packetId;
	UserId userId;
	char username[sMAX_USERNAME_LENGTH];

	RequestJoinServerPacket(UserId userId, const std::string& name) :
		packetId(andrick_ID_REQUEST_JOIN_SERVER),
		userId(userId)
	{
		strcpy(username, name.c_str());
	}
};
#pragma pack(pop)

//Server sends to client that just joined.
//Server sends private welcome message to client.
#pragma pack(push, 1)
struct JoinAcceptedPacket
{
	PacketEventId packetId;

	//The server assigns the client a userId and sends it to them!
	char username[sMAX_USERNAME_LENGTH];

	//The maximum amount of users that can be on the server.
	char maxUserCount;
	char connectedUserCount;

	JoinAcceptedPacket(const std::string& name, char maxUsers, char currentUserCount) : //, char userInfo[][sMAX_USERNAME_LENGTH + 1]) :
		packetId(andrick_ID_JOIN_ACCEPTED),
		maxUserCount(maxUsers),
		connectedUserCount(currentUserCount)
	{
		strcpy(username, name.c_str());
	}
};
#pragma pack(pop)

#pragma pack(push, 1)
struct JoinFailedPacket
{
	PacketEventId packetId;
	UserId userId;
	char errorMessage[sMAX_MESSAGE_LENGTH];

	JoinFailedPacket(UserId userId, const std::string& message) :
		packetId(andrick_ID_JOIN_FAILED),
		userId(userId)
	{
		strcpy(errorMessage, message.c_str());
	}
};
#pragma pack(pop)

//Server sends to everyone else in the chat that someone joined.
//Server sends a public message saying this user joined.
#pragma pack(push, 1)
struct NewUserJoinedServerPacket
{
	PacketEventId packetId;
	UserId userId;
	char username[sMAX_USERNAME_LENGTH];

	NewUserJoinedServerPacket(UserId user, const std::string& name/*, char currentUserCount, char userInfo[sMAX_USERS][sMAX_USERNAME_LENGTH + 1]*/) :
		packetId(andrick_ID_USER_JOINED_SERVER),
		userId(user),
		username()
	{
		strcpy(username, name.c_str());
	}
};
#pragma pack(pop)

//Client that left sends this to the server.
//The server sends this to everyone in the chat.
//The server then sends a public message saying this user left.
#pragma pack(push, 1)
struct UserDisconnectedPacket
{
	PacketEventId packetId;
	UserId userId;

	UserDisconnectedPacket(UserId user) :
		packetId(andrick_ID_USER_DISCONNECTED),
		userId(user)
	{

	}
};
#pragma pack(pop)

#pragma pack(push, 1)
struct ServerClosingPacket
{
	PacketEventId packetId;

	ServerClosingPacket() :
		packetId(andrick_ID_SERVER_CLOSING)
	{

	}
};
#pragma pack(pop)

//The message sent to host asking to be delivered
#pragma pack(push, 1)
struct SendPublicMessageRequestPacket
{
	PacketEventId packetId;
	UserId userId;
	char message[sMAX_MESSAGE_LENGTH];
	char msgType;

	SendPublicMessageRequestPacket(UserId user, const std::string& newMessage, MessageType type = MessageType::GLOBAL) :
		packetId(andrick_ID_SEND_PUBLIC_MESSAGE_REQUEST),
		userId(user),
		msgType((char)type)
	{
		strcpy(message, newMessage.c_str());
	}
};
#pragma pack(pop)

#pragma pack(push, 1)
struct SendPrivateMessageRequestPacket
{
	PacketEventId packetId;
	UserId fromUserId;
	char toUsername[sMAX_MESSAGE_LENGTH];
	char message[sMAX_MESSAGE_LENGTH];

	SendPrivateMessageRequestPacket(UserId fromUser, const std::string& toUser, const std::string& newMessage) :
		packetId(andrick_ID_SEND_PRIVATE_MESSAGE_REQUEST),
		fromUserId(fromUser)
	{
		strcpy(message, newMessage.c_str());
		strcpy(toUsername, toUser.c_str());
	}
};
#pragma pack(pop)

//A message sent out. Broadcast by Host
#pragma pack(push, 1)
struct DeliverPublicMessagePacket
{
	PacketEventId packetId;
	UserId userId;
	char message[sMAX_MESSAGE_LENGTH];
	char msgType;

	//TODO: init user id also at some point
	DeliverPublicMessagePacket(UserId user, const std::string& newMessage, MessageType type = MessageType::GLOBAL) :
		packetId(andrick_ID_DELIVER_PUBLIC_MESSAGE),
		userId(user),
		msgType((char)type)
	{
		strcpy(message, newMessage.c_str());
	}
};
#pragma pack(pop)

#pragma pack(push, 1)
struct DeliverPrivateMessagePacket
{
	PacketEventId packetId;
	UserId fromUserId;
	UserId toUserId;
	char message[sMAX_MESSAGE_LENGTH];

	DeliverPrivateMessagePacket(UserId fromUser, UserId toUser, const std::string& newMessage) :
		packetId(andrick_ID_DELIVER_PRIVATE_MESSAGE),
		fromUserId(fromUser),
		toUserId(toUser)
	{
		strcpy(message, newMessage.c_str());
	}
};
#pragma pack(pop)


//A message sent out. Broadcast by Host
#pragma pack(push, 1)
struct MessagePacket
{
	PacketEventId packetId;
	char message[sMAX_MESSAGE_LENGTH];

	//TODO: init user id also at some point
	MessagePacket(const std::string& newMessage) :
		packetId(andrick_ID_SEND_MESSAGE)
	{
		strcpy(message, newMessage.c_str());
	}
};
#pragma pack(pop)


#pragma pack(push, 1)
struct WhisperPacket
{
	PacketEventId packetId;
	UserId senderId;
	UserId recieverId;
	char message[sMAX_MESSAGE_LENGTH];

	WhisperPacket(UserId sender, UserId reciever, const std::string& newMessage) :
		packetId(andrick_ID_WHISPER_COMMAND),
		senderId(sender),
		recieverId(reciever)
	{
		strcpy(message, newMessage.c_str());
	}
};
#pragma pack(pop)

#pragma pack(push, 1)
struct structName
{
unsigned char useTimeStamp; // Assign ID_TIMESTAMP to this
RakNet::Time timeStamp; // Put the system time in here returned by RakNet::GetTime() or some other method that returns a similar value
unsigned char typeId; // Your type here
// Your data here
};
#pragma pack(pop)

#endif