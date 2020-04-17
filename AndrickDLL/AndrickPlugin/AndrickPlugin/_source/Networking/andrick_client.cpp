#include <_source/Networking/andrick_client.h>
//#include <A3_DEMO/_andrick_Network/_andrick_Packet/andrick_packethandler.h>

Client::Client(bool isRemote) :
	mIsRemoteUser(isRemote),
	mAuthority(AuthorityId::NORMAL),
	mUserId(-1),
	mServersMaxUserCount(0),
	mClientMap({})
{}

void Client::setUserId(const UserId id)
{
	mUserId = id;
}

void Client::setUsername(const std::string& username)
{
	mUsername = username;
}

void Client::setAuthority(AuthorityId authority)
{
	mAuthority = authority;
}

const UserId& Client::getId() const
{
	return mUserId;
}

const std::string& Client::getUsername() const
{
	return mUsername;
}

const AuthorityId& Client::getAuthority() const
{
	return mAuthority;
}

//void Client::processIncomingEvent(std::shared_ptr<struct Event> evnt)
//{
//	///We can just use execute() in the future if necessary, but for now, switch is fine.
//
//	switch (evnt->eventId)
//	{
//		case EventId::CONNECTION_NEW_USER_JOINED:
//		{
//			evnt->execute();
//			break;
//		}
//		case EventId::USER_DISCONNECTED:
//		{
//			evnt->execute();
//			break;
//		}
//		default:
//			break;
//	}
//}

bool Client::getClientFromUsername(const std::string& username, std::shared_ptr<Client>& out)
{
	bool success = false;
	out = nullptr;

	for (auto iter = mClientMap.begin(); iter != mClientMap.end(); ++iter)
	{
		if (iter->second->getUsername().compare(username) == 0)
		{
			out = iter->second;
			success = true;
			break;
		}
	}

	return success;
}

void Client::initNewUser(const UserId id, const std::string& username)
{
	std::shared_ptr<Client> newUser = std::make_shared<Client>(true);
	newUser->setUserId(id);
	newUser->setUsername(username);
	newUser->setAuthority(AuthorityId::NORMAL);///TODO: Send this over the network.
	mClientMap.insert({ id, newUser });
}