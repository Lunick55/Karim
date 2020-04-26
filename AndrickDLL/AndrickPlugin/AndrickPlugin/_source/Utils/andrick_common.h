#ifndef COMMON_H_
#define COMMON_H_

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <map>
#include <RakTits/RakPeerInterface.h>
#include <RakTits/MessageIdentifiers.h>

typedef char UserId;
typedef unsigned int UnitID;

static const int INVALID_USER_ID = -1;
static const int sMAX_USERNAME_LENGTH = 20;
static const int sMAX_USERS = 64;
static const int sMAX_MESSAGE_LENGTH = 128;
static const int sDEFAULT_MAX_USERS = 10;
//static const int sPORT = 12975;
static const int sPORT = 5555;

static const int MAX_INPUT_LENGTH = 512;

static constexpr int BOID_COUNT = 1;

extern class EventSystem& gEventSystem;
extern class NetworkManager& gNetManager;

int initializeServer(int maxUsers);
int initializeClient(char* ip);

enum class CommandId : char
{
	INVALID_COMMAND = -1,
	LIST_PLAYERS,
	WHISPER,
};

enum class EventId : char
{
	INVALID_EVENT = -1,
	NEW_INCOMING_CONNECTION,///Client -> Server - see if we can get inital connection
	CONNECTION_REQUEST_ACCEPTED,///Server -> Client - server got the connection and you can join
	CONNECTION_REQUEST_FAILED,///Server -> Client - server got the connection but it's full so bye
	CONNECTION_REQUEST_JOIN,///Client -> Server - client asks if it can join with andrick specific data (username, authority, etc)
	CONNECTION_JOIN_ACCEPTED,///Server -> Client - Everything is good, you can enter the server
	CONNECTION_JOIN_FAILED,///Server -> Client - Disconnect a user
	CONNECTION_NEW_USER_JOINED,///Server -> All Clients - A new user joined the server
	USER_DISCONNECTED,///Disconnected Client -> Server. Server -> All Clients - A client left the server
	CHAT_MESSAGE,
	MESSAGE,
	INCREMENT_THE_SPACE,
	//GENERIC_EVENT,
	BOID_DATA_EVENT,
	COMMAND
};

const enum class MessageType : unsigned char
{
	GLOBAL,
	SPECTOR,
	PLAYER
};

enum class AuthorityId : unsigned char
{
	NORMAL,
	MODERATOR,
	ADMIN
};

enum PacketEventId : unsigned char
{
	andrick_ID_SET_AUTHORITY = ID_USER_PACKET_ENUM,

	andrick_ID_SEND_PUBLIC_MESSAGE_REQUEST,		//Clientside command
	andrick_ID_SEND_PRIVATE_MESSAGE_REQUEST,	//Clientside command

	andrick_ID_DELIVER_PUBLIC_MESSAGE,			//Serverside command
	andrick_ID_DELIVER_PRIVATE_MESSAGE,			//Serverside command

	andrick_ID_SEND_MESSAGE,

	andrick_ID_CONNECTION_REQUEST_ACCEPTED,
	andrick_ID_CONNECTION_ATTEMPT_FAILED,
	andrick_ID_REQUEST_JOIN_SERVER,				//Client asks server to join
	andrick_ID_JOIN_ACCEPTED,					//Server sends a welcome message to joined user
	andrick_ID_JOIN_FAILED,						//Server sends this to client, client disconnects
	andrick_ID_USER_JOINED_SERVER,				//Server notifies everyone a user joined

	andrick_ID_USER_DISCONNECTED,
	andrick_ID_SERVER_CLOSING,

	////////////////////////

	andrick_ID_MUTE_USER,
	andrick_ID_UNMUTE_USER,

	andrick_ID_WHISPER_COMMAND,


	//////////////////////////
	// BOID EVENT TYPES
	//////////////////////////

	andrick_ID_BOID_DATA_PUSH_EVENT,
	andrick_ID_BOID_DATA_SHARE_EVENT,
	andrick_ID_BOID_DATA_COUPLE_EVENT,

	//////////////////////////

	andrick_ID_SERVER_TRAVEL,
	andrick_ID_UPDATE_TICTAC_STATE,
	andrick_ID_SETUP_TICTAC_GAME,
	andrick_ID_UPDATE_BATTLE_STATE,
	andrick_ID_SETUP_BATTLE_GAME,
	andrick_ID_ASK_IF_BATTLE_HIT,
	andrick_ID_REPLY_IF_BATTLE_HIT
};

#ifdef __cplusplus
extern "C"
{
#endif
	// C header here
	extern int shutdownRakNet();
	extern RakNet::Time getTime();
#ifdef __cplusplus
}
#endif

#endif