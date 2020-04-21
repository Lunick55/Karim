#include <_source/Utils/andrick_common.h>
#include <_source/Utils/network_manager.h>

void ActivateServer()
{
	NetworkManager::get();
	EventSystem::get();

	gNetManager.mpServer = nullptr;
	gNetManager.mpClient = nullptr;
	gNetManager.mpPacketHandler = nullptr;

	initializeServer();
}

bool TestMeDaddy()
{
	return true;
}