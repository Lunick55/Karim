#include <_source/Networking/andrick_server.h>
//#include <A3_DEMO/_andrick_Network/_andrick_Packet/andrick_packethandler.h>

UserId Server::sUserIdCounter = 0;

Server::Server() :
	mMaxUsers(0),
	mConnectedUserMap({})
{

}

//void Server::processIncomingEvent(std::shared_ptr<struct Event> evnt)
//{
//	switch (evnt->eventId)
//	{
//	case EventId::NEW_INCOMING_CONNECTION:
//	{
//		std::cout << "A new user is attempting to connect!" << std::endl;
//		evnt->execute();
//		break;
//	}
//	case EventId::CONNECTION_REQUEST_JOIN:
//	{
//		std::cout << "A new user is requesting to join the server!" << std::endl;
//		evnt->execute();
//		break;
//	}
//	case EventId::CONNECTION_JOIN_FAILED:
//	{
//		evnt->execute();
//		break;
//	}
//	case EventId::USER_DISCONNECTED:
//	{
//		evnt->execute();
//		break;
//	}
//	default:
//		break;
//	}
//}

//bool Server::processNewIncomingUser(RakNet::SystemAddress clientAddress, UserId& newUserId, std::string& errorMessage)
//{
//	if (mConnectedUserMap.size() < gDemoState->mpPacketHandler->getMaxConnections())
//	{
//		std::shared_ptr<Client> newUser = std::make_shared<Client>(true);
//		newUser->setAddress(clientAddress);
//		newUser->setUserId(sUserIdCounter++);
//		newUserId = newUser->getId();
//		newUser->setUsername("Noob" + std::to_string(newUserId));
//		newUser->setAuthority(AuthorityId::NORMAL);
//		mConnectedUserMap.insert({ newUser->getId(), newUser });
//		std::cout << "Adding new user to server map: " << newUser->getUsername() << std::endl;
//		return true;
//	}
//	else
//	{
//		errorMessage = "The server is currently full! Try again later. :(";
//		newUserId = -1;
//	}
//
//	return false;
//}

bool Server::getClientById(UserId userId, std::shared_ptr<Client>& out)
{
	std::map<UserId, std::shared_ptr<Client>>::iterator iter = mConnectedUserMap.find(userId);
	if (iter != mConnectedUserMap.end())
	{
		out = iter->second;
		return true;
	}

	return false;
}

bool Server::isUsernameTaken(const std::string& username)
{
	for (auto iter = mConnectedUserMap.begin(); iter != mConnectedUserMap.end(); ++iter)
	{
		if (iter->second->getUsername().compare(username) == 0)
		{
			return true;
		}
	}

	return false;
}

bool Server::disconnectClient(const UserId& id)
{
	//if (gDemoState->mpPacketHandler && gDemoState->mpPacketHandler->mpPeer)
	//{
	//	std::shared_ptr<Client> out;
	//	if (gDemoState->mpServer->getClientById(id, out))
	//	{
	//		gDemoState->mpPacketHandler->mpPeer->CloseConnection(out->getAddress(), true);
	//		mConnectedUserMap.erase(out->getId());
	//		return true;
	//	}
	//}

	return false;
}