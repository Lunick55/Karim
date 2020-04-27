#include <_source/Utils/andrick_common.h>
#include <_source/Networking/andrick_server.h>
#include <_source/Event/andrick_eventsystem.h>
#include <_source/Utils/network_manager.h>
#include <_source/Networking/andrick_client.h>
#include <_source/Networking/Packet/andrick_packethandler.h>

#include <chrono>

EventSystem& gEventSystem = EventSystem::get();
NetworkManager& gNetManager = NetworkManager::get();

bool initializeServer(int maxUsers)
{
	gNetManager.mpServer = std::make_shared<Server>();
	gEventSystem.addListener(gNetManager.mpServer, EventProcessingType::SERVERSIDE);
	gNetManager.mpServer->isActive = true;
	gNetManager.mpPacketHandler = std::make_shared<PacketHandler>();
	std::cout << "Initializing server and server packet handler!" << std::endl;

	gNetManager.mpServer->setMaxUsers(maxUsers);

	if (gNetManager.mpPacketHandler->startup((int)gNetManager.mpServer->getMaxUserCount()))
	{
		//printf("\nServer spinning up... \n");
		return true;
	}
	else
	{
		return false;
	}
}

bool initializeClient(char* ip, char* username)
{
	gNetManager.mpClient = std::make_shared<Client>();
	gEventSystem.addListener(gNetManager.mpClient, EventProcessingType::CLIENTSIDE);
	gNetManager.mpPacketHandler = std::make_shared<PacketHandler>();
	std::cout << "Initializing client packet handler!" << std::endl;

	if (gNetManager.mpPacketHandler->startup(1))
	{
		if (gNetManager.mpPacketHandler->connect(ip))
		{
			//std::cout << "Client spinning up..." << std::endl;
			gNetManager.mpClient->setUsername(username);
			return true;
		}
		else
		{
			//std::cout << "Failed to connect to server." << std::endl;
			return false;
		}
	}
	return false;
}

#ifdef __cplusplus
extern "C"
{
#endif
	// C header here

	int shutdownRakNet()
	{
		int result = 0;
		if (gNetManager.mpServer)
		{
			gEventSystem.removeListener(gNetManager.mpServer);
			gNetManager.mpServer.reset();
			result += 1;
		}
		
		if (gNetManager.mpClient)
		{
			gEventSystem.removeListener(gNetManager.mpClient);
			gNetManager.mpClient.reset();
			result += 1;
		}
		
		if (gNetManager.mpPacketHandler)
		{
			if (gNetManager.mpPacketHandler->disconnect())
			{
				std::cout << "Successfully disconnected." << std::endl;
				result += 1;
				if (gNetManager.mpPacketHandler->shutdown())
				{
					std::cout << "Successfully shutdown RakNet." << std::endl;
					result += 1;
				}
			}
		}

		//haha am programmer
		if (result < 3)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}

	RakNet::Time getTime()
	{
		using namespace std::chrono;
		milliseconds ms = duration_cast<milliseconds>(
			system_clock::now().time_since_epoch()
			);
		//std::printf("Time: %I64i\n", ms.count());

		return ms.count();
	}

#ifdef __cplusplus
}
#endif