#include <_source/Utils/andrick_common.h>
#include <_source/Networking/andrick_server.h>
#include <_source/Event/andrick_eventsystem.h>
#include <_source/Utils/network_manager.h>
#include <_source/Networking/andrick_client.h>
#include <_source/Networking/Packet/andrick_packethandler.h>

#include <chrono>

EventSystem& gEventSystem = EventSystem::get();
NetworkManager& gNetManager = NetworkManager::get();

#ifdef __cplusplus
extern "C"
{
#endif
	// C header here
	void initializeServer()
	{
		gNetManager.mpServer = std::make_shared<Server>();
		gEventSystem.addListener(gNetManager.mpServer, EventProcessingType::SERVERSIDE);
		gNetManager.mpServer->isActive = true;
		//Packet handler is singleton now. Next line should be irrelevant
		gNetManager.mpPacketHandler = std::make_shared<PacketHandler>();
		std::cout << "Initializing server and server packet handler!" << std::endl;
	}

	void initializeClient()
	{
		gNetManager.mpClient = std::make_shared<Client>();
		gEventSystem.addListener(gNetManager.mpClient, EventProcessingType::CLIENTSIDE);
		gNetManager.mpPacketHandler = std::make_shared<PacketHandler>();
		std::cout << "Initializing client packet handler!" << std::endl;
	}

	void shutdownRakNet()
	{
		if (gNetManager.mpServer)
		{
			gEventSystem.removeListener(gNetManager.mpServer);
			gNetManager.mpServer.reset();
		}
		
		if (gNetManager.mpClient->isActive)
		{
			gEventSystem.removeListener(gNetManager.mpClient);
			gNetManager.mpClient.reset();
		}
		
		if (gNetManager.mpPacketHandler)
		{
			if (gNetManager.mpPacketHandler->disconnect())
			{
				std::cout << "Successfully disconnected." << std::endl;
				if (gNetManager.mpPacketHandler->shutdown())
				{
					std::cout << "Successfully shutdown RakNet." << std::endl;
				}
			}
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