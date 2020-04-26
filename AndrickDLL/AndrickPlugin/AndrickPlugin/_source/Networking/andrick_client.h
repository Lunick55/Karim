#ifndef CLIENT_H_
#define CLIENT_H_

#include <_source/Utils/andrick_common.h>
#include <_source/Event/andrick_eventSystem.h>
#include <queue>

class Client : public EventListener
{
public:
	Client();
	virtual ~Client() = default;

	void processIncomingEvent(std::shared_ptr<struct Event> evnt) override;
	void initNewUser(const UserId id, const std::string& username);

	//These are all clientside functions.
	//The server has it's own copy of clients and
	//verifies userId/username/authority don't change
	//without permission.
	void setUserId(const UserId id);
	void setUsername(const std::string& username);
	void setAuthority(AuthorityId authority);
	void setAddress(const RakNet::SystemAddress& address) { mAddress = address; }

	bool getClientFromUsername(const std::string& username, std::shared_ptr<Client>& out);
	const UserId& getId() const;
	const std::string& getUsername() const;
	const AuthorityId& getAuthority() const;
	const RakNet::SystemAddress& getAddress() const { return mAddress; };

	inline void setServersMaxUserCount(std::size_t maxUsers) { mServersMaxUserCount = maxUsers; };
	inline void setConnectedUserCount(std::size_t maxUsers) { mConnectedUserCount = maxUsers; };
	inline std::size_t getMaxUserCount() const { return mServersMaxUserCount; };
	inline std::size_t getConnectedUserCount() const { return mConnectedUserCount; };

	bool isActive = false;
	int chatlogNextLength = 50;
	std::queue<std::string> chatlog;

private:
	UserId mUserId;
	std::string mUsername;
	AuthorityId mAuthority;
	RakNet::SystemAddress mAddress;

	std::size_t mServersMaxUserCount;
	std::size_t mConnectedUserCount;

	std::map<UserId, std::shared_ptr<Client>> mClientMap;

};

#endif