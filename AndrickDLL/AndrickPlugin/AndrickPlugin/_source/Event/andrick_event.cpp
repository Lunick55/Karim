#include  <_source/Event/andrick_event.h>
#include <_source/Networking/Packet/andrick_packet.h>
#include <_source/Networking/andrick_client.h>
#include <_source/Networking/andrick_server.h>
#include <_source/Networking/Packet/andrick_packethandler.h>
#include <_source/Utils/network_manager.h>

///Client -> Server - see if we can get inital connection
#pragma region NewIncomingConnectionEvent
void NewIncomingConnectionEvent::execute()
{
	std::cout << "New incoming connection..." << std::endl;

	//Check if we have room.
	UserId userId;
	std::string errorMessage;

	std::shared_ptr<SendableEvent> evnt;

	//Send an accepted/failed event to the client
	if (gNetManager.mpServer->processNewIncomingUser(clientAddress, userId, errorMessage))
	{
		evnt = std::make_shared<ConnectionRequestAcceptedEvent>(gNetManager.mpPacketHandler->getServerAddress(), userId, false, userId);
		gEventSystem.queueNetworkEvent(evnt);
		//auto userMap = gDemoState->mpServer->getConnectedUsers();
		//for (auto iter = userMap.begin(); iter != userMap.end(); ++iter)
		//{
		//	std::shared_ptr<SendableEvent> connectedUserData = std::make_shared<BoidDataEvent>(
		//		andrick_ID_BOID_DATA_PUSH_EVENT, iter->second->->boids, boidEvntPacket->senderId
		//	);
		//
		//	gEventSystem.queueNetworkEvent(connectedUserData);
		//}
	}
	else
	{
		evnt = std::make_shared<ConnectionRequestFailedEvent>(clientAddress, errorMessage);
		gEventSystem.queueNetworkEvent(evnt);
	}

}
#pragma endregion

///Server -> Client - server got the connection and you can join
#pragma region ConnectionRequestAcceptedEvent
ConnectionRequestAcceptedEvent::ConnectionRequestAcceptedEvent(RakNet::SystemAddress serverAddress, UserId newUserId,
	bool isBroadcast, UserId receiverId) :
	SendableEvent(EventId::CONNECTION_REQUEST_ACCEPTED, EventProcessingType::CLIENTSIDE, isBroadcast, receiverId),
	serverAddress(serverAddress),
	newUserId(newUserId) {}

void ConnectionRequestAcceptedEvent::execute()
{
	gNetManager.mpPacketHandler->setServerAddress(serverAddress);
	gNetManager.mpClient->setUserId(newUserId);
	std::cout << "Our connection request was accepted! UserId: " << std::to_string(newUserId) << std::endl;
}

std::size_t ConnectionRequestAcceptedEvent::allocatePacket(char*& out)
{
	std::size_t packetSize = sizeof(ConnectionRequestAcceptedPacket);
	out = (char*)malloc(packetSize);
	memcpy(out, (char*)&ConnectionRequestAcceptedPacket(newUserId), packetSize);
	return packetSize;
}
#pragma endregion

///Server -> Client - server got the connection but it's full so bye
#pragma region ConnectionRequestFailedEvent
void ConnectionRequestFailedEvent::execute()
{
	std::cout << "Our connection request failed:\n\t" << errorMessage << std::endl;
}

std::size_t ConnectionRequestFailedEvent::allocatePacket(char*& out)
{
	std::size_t packetSize = sizeof(ConnectionRequestFailedPacket);
	out = (char*)malloc(packetSize);
	memcpy(out, (char*)&ConnectionRequestFailedPacket(errorMessage), packetSize);
	return packetSize;
}
#pragma endregion

///Client -> Server - client asks if it can join with andrick specific 
///data (username, authority, etc)
#pragma region ConnectionRequestJoinEvent
ConnectionRequestJoinEvent::ConnectionRequestJoinEvent(UserId userId, const std::string& username,
	bool isBroadcast, UserId receiverId) :
	SendableEvent(EventId::CONNECTION_REQUEST_JOIN, EventProcessingType::SERVERSIDE, isBroadcast, receiverId),
	mUsername(username),
	mUserId(userId)
{

}

void ConnectionRequestJoinEvent::execute()
{
	if (gNetManager.mpServer->isUsernameTaken(mUsername))
	{
		std::cout << "USER NAME IS TAKEN" << std::endl;
		std::shared_ptr<SendableEvent> joinFailedEvnt = std::make_shared<ConnectionJoinFailedEvent>(mUserId,
			"Sorry, that username is already taken.");

		gEventSystem.queueNetworkEvent(joinFailedEvnt);
	}
	else
	{
		std::shared_ptr<Client> out;
		if (gNetManager.mpServer->getClientById(mUserId, out))
		{
			out->setUsername(mUsername);
		}

		std::shared_ptr<SendableEvent> privateEvnt = std::make_shared<ConnectionJoinAcceptedEvent>(mUsername,
			gNetManager.mpServer->getMaxUserCount(), gNetManager.mpServer->getConnectedUserCount(),
			false, mUserId);

		std::shared_ptr<SendableEvent> broadcastEvnt = std::make_shared<ConnectionNewUserJoinedEvent>(mUserId, mUsername);

		gEventSystem.queueNetworkEvent(privateEvnt);
		gEventSystem.queueNetworkEvent(broadcastEvnt);
	}
}

std::size_t ConnectionRequestJoinEvent::allocatePacket(char*& out)
{
	std::size_t packetSize = sizeof(RequestJoinServerPacket);
	out = (char*)malloc(packetSize);
	memcpy(out, (char*)&RequestJoinServerPacket(mUserId, mUsername), packetSize);
	return packetSize;
}
#pragma endregion

///Server -> Client - Everything is good, you can enter the server
#pragma region ConnectionJoinAcceptedEvent

ConnectionJoinAcceptedEvent::ConnectionJoinAcceptedEvent(const std::string& username, std::size_t maxUserCount, std::size_t connectedUserCount,
	bool isBroadcast, UserId receiverId) :
	SendableEvent(EventId::CONNECTION_JOIN_ACCEPTED, EventProcessingType::CLIENTSIDE, isBroadcast, receiverId),
	mUsername(username), mMaxUserCount(maxUserCount), mConnectedUserCount(connectedUserCount)
{
	///TODO: Take in an array of connected user data to populate mpClientMap
}

void ConnectionJoinAcceptedEvent::execute()
{
	gNetManager.mpClient->setServersMaxUserCount(mMaxUserCount);
	gNetManager.mpClient->setConnectedUserCount(mConnectedUserCount);
	gNetManager.mpClient->setUsername(mUsername);
	///TODO: Send over client data from server and initialize the mpClientMap

	std::cout << mUsername << " successfully joined the server! - " << std::to_string(mConnectedUserCount) << "/" << std::to_string(mMaxUserCount) << " online." << std::endl;
}

std::size_t ConnectionJoinAcceptedEvent::allocatePacket(char*& out)
{
	std::size_t packetSize = sizeof(JoinAcceptedPacket);
	out = (char*)malloc(packetSize);
	memcpy(out, (char*)&JoinAcceptedPacket(mUsername, (char)mMaxUserCount, (char)mConnectedUserCount), packetSize);
	return packetSize;
}

#pragma endregion

#pragma region ConnectionJoinFailedEvent

ConnectionJoinFailedEvent::ConnectionJoinFailedEvent(UserId userId, const std::string& errorMessage) :
	SendableEvent(EventId::CONNECTION_JOIN_FAILED, EventProcessingType::BOTH, false, userId),
	userId(userId), errorMessage(errorMessage)
{

}

void ConnectionJoinFailedEvent::execute()
{
	if (gNetManager.mpPacketHandler->isServer())
	{
		if (gNetManager.mpServer->disconnectClient(userId))
		{
			std::cout << "Disconnecting client because they have an invalid username." << std::endl;
		}
	}
	else
	{
		std::cout << "You got disconnected by the server for having an invalid username." << std::endl;
		
		std::shared_ptr<SendableEvent> joinFailedEvnt = std::make_shared<ConnectionJoinFailedEvent>(userId,
			"Closing client connection.");

		gEventSystem.queueNetworkEvent(joinFailedEvnt);
	}
}

std::size_t ConnectionJoinFailedEvent::allocatePacket(char*& out)
{
	std::size_t packetSize = sizeof(JoinFailedPacket);
	out = (char*)malloc(packetSize);
	memcpy(out, (char*)&JoinFailedPacket(userId, errorMessage), packetSize);
	return packetSize;
}

#pragma endregion


///Server -> All Clients - A new user joined the server
#pragma region ConnectionNewUserJoinedEvent

ConnectionNewUserJoinedEvent::ConnectionNewUserJoinedEvent(UserId user, const std::string& username,
	bool isBroadcast, UserId receiverId) :
	SendableEvent(EventId::CONNECTION_REQUEST_ACCEPTED, EventProcessingType::CLIENTSIDE, isBroadcast, receiverId),
	mUserId(user), mUsername(username)
{

}

void ConnectionNewUserJoinedEvent::execute()
{
	std::cout << "A new user has just joined the server. Don't be shy, say hi to " << mUsername << "!" << std::endl;
	
	if (mUserId != gNetManager.mpClient->getId())
	{
		gNetManager.mpClient->initNewUser(mUserId, mUsername);
	}
}

std::size_t ConnectionNewUserJoinedEvent::allocatePacket(char*& out)
{
	std::size_t packetSize = sizeof(NewUserJoinedServerPacket);
	out = (char*)malloc(packetSize);
	memcpy(out, (char*)&NewUserJoinedServerPacket(mUserId, mUsername), packetSize);
	return packetSize;
}

#pragma endregion

//#pragma region GenericEvent
//std::size_t GenericEvent::allocatePacket(char*& out)
//{
//	std::size_t packetSize = sizeof(GenericEventPacket);
//	out = (char*)malloc(packetSize);
//	memcpy(out, (char*)&GenericEventPacket(packetId, userId), packetSize);
//	return packetSize;
//}
//#pragma endregion

//#pragma region CommandEvent
//CommandEvent::CommandEvent(std::shared_ptr<Command> command, bool isBroadcast, UserId receiverId) :
//	SendableEvent(EventId::COMMAND, EventProcessingType::BOTH, isBroadcast, receiverId),
//	command(command) {}
//
//void CommandEvent::execute() 
//{ 
//	command->runCommand(); 
//}
//#pragma endregion
//
//#pragma region WhisperCommandEvent
//WhisperCommandEvent::WhisperCommandEvent(std::shared_ptr<WhisperCommand> command) :
//	CommandEvent(command, false, command->mpReciever->getId()) {}
//
//std::size_t WhisperCommandEvent::allocatePacket(char*& out)
//{
//	std::shared_ptr<WhisperCommand> whisperCommandData = std::dynamic_pointer_cast<WhisperCommand>(command);
//	std::size_t packetSize = sizeof(WhisperPacket);
//	out = (char*)malloc(packetSize);
//	memcpy(out, (char*)&WhisperPacket(whisperCommandData->mpSender->getId(), whisperCommandData->mpReciever->getId(), whisperCommandData->mMessage.c_str()), packetSize);
//	return packetSize;
//}
//#pragma endregion

#pragma region UserDisconnectedEvent

UserDisconnectedEvent::UserDisconnectedEvent(UserId userId) :
	SendableEvent(EventId::USER_DISCONNECTED, EventProcessingType::BOTH, gNetManager.mpPacketHandler->isServer()),
	userId(userId)
{

}

void UserDisconnectedEvent::execute()
{
	std::cout << "User disconnected!" << std::endl;
	std::shared_ptr<SendableEvent> userDisconnectedEvnt = std::make_shared<UserDisconnectedEvent>(userId);
	gEventSystem.queueNetworkEvent(userDisconnectedEvnt);

	if (gNetManager.mpPacketHandler->isServer())
	{
		gNetManager.mpServer->disconnectClient(userId);
	}
	else if (gNetManager.mpClient->getId() == userId)
	{
		gNetManager.mpPacketHandler->disconnect();
	}
	else
	{
		///TODO: Use the clientside map. For now just use count until we send over user data.
		gNetManager.mpClient->setConnectedUserCount(gNetManager.mpClient->getConnectedUserCount() - 1);
	}
}

std::size_t UserDisconnectedEvent::allocatePacket(char*& out)
{
	std::size_t packetSize = sizeof(UserDisconnectedPacket);
	out = (char*)malloc(packetSize);
	memcpy(out, (char*)&UserDisconnectedPacket(userId), packetSize);
	return packetSize;
}

#pragma endregion

#pragma region MessageEvent

MessageEvent::MessageEvent(const std::string& message) :
	SendableEvent(EventId::MESSAGE, EventProcessingType::BOTH, gNetManager.mpPacketHandler->isServer()),
	mMessage(message)
{

}

void MessageEvent::execute()
{
	if (gNetManager.mpServer)
	{
		std::shared_ptr<MessageEvent> packetData = std::make_shared<MessageEvent>(std::string(mMessage));
		gEventSystem.queueNetworkEvent(packetData);
	}
	else if (gNetManager.mpClient)
	{
		//add to vector
		if (gNetManager.mpClient->chatlog.size() >= gNetManager.mpClient->chatlogNextLength)
		{
			gNetManager.mpClient->chatlog.pop();
		}
		gNetManager.mpClient->chatlog.push(mMessage);
	}
}

std::size_t MessageEvent::allocatePacket(char*& out)
{
	std::size_t packetSize = sizeof(MessagePacket);
	out = (char*)malloc(packetSize);
	memcpy(out, (char*)&MessagePacket(mMessage), packetSize);
	return packetSize;
}

#pragma endregion