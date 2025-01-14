#include <_source/Event/andrick_eventsystem.h>
#include <_source/Networking/Packet/andrick_packethandler.h>
#include <_source/Networking/andrick_server.h>
#include <_source/Utils/network_manager.h>

void EventSystem::addListener(EventId eventId, FuncPtr func)
{	
	std::shared_ptr<FuncPtr> funcWrapper = std::make_shared<FuncPtr>(func);
	//TODO: maybe check if contained already?
	mListenerFuncMap.insert({ eventId, funcWrapper });
}

void EventSystem::addListener(std::shared_ptr<EventListener> evntListener, EventProcessingType processingType)
{
	std::map<std::shared_ptr<EventListener>, EventProcessingType>::iterator iter = mEventListeners.begin();

	for (; iter != mEventListeners.end(); ++iter)
	{
		if (iter->first == evntListener)
		{
			return;
		}
	}

	mEventListeners.insert({ evntListener, processingType });
}

void EventSystem::removeListener(EventId eventId, FuncPtr func)
{
	std::shared_ptr<FuncPtr> funcWrapper = std::make_shared<FuncPtr>(func);
	//should get me all the values with the key
	//std::pair<MMAPIterator, MMAPIterator> result = mmapOfPos.equal_range('c');
	std::pair<MultMap::iterator, MultMap::iterator> multKeyResult = mListenerFuncMap.equal_range(eventId);

	MultMap::iterator iter = multKeyResult.first;

	//iterate through those key vlaues, and fire events!
	//for (MMAPIterator it = result.first; it != result.second; it++)
	for (; iter != multKeyResult.second; ++iter)
	{
		//TODO: handle this somehow
		//std::functions are incomparable, must wrap them in a shared_ptr to compare
		if (iter->second == funcWrapper)
		{
			mListenerFuncMap.erase(iter);
			return;
		}
	}
}

void EventSystem::removeListener(std::shared_ptr<EventListener> evntListener)
{
	std::map<std::shared_ptr<EventListener>, EventProcessingType>::iterator iter = mEventListeners.begin();

	for (; iter != mEventListeners.end(); ++iter)
	{
		if (iter->first == evntListener)
		{
			mEventListeners.erase(iter);
			return;
		}
	}
}

void EventSystem::queueLocalEvent(std::shared_ptr<Event> eventData)
{
	eventData->dispatchType = EventDispatchType::LOCAL;
	mQueuedLocalEvents.push(eventData);
}

void EventSystem::queueNetworkEvent(std::shared_ptr<SendableEvent> eventData)
{
	eventData->dispatchType = EventDispatchType::NETWORK;
	mQueuedNetworkEvents.push(eventData);
}

//Executes all of the queued local events.
//Events coming in from over the network get
//queued up in here as well as general local 
//events from the client
void EventSystem::executeQueuedLocalEvents()
{
	while (!mQueuedLocalEvents.empty())
	{
		std::shared_ptr<Event> eventData = mQueuedLocalEvents.front();
		mQueuedLocalEvents.pop();

		//should get me all the values with the key
		//then iterate through those key vlaues, and fire events!
		std::pair<MultMap::iterator, MultMap::iterator> multKeyResult = mListenerFuncMap.equal_range(eventData->eventId);

		MultMap::iterator multMapIter;
		for (multMapIter = multKeyResult.first; multMapIter != multKeyResult.second; multMapIter++)
		{
			(*multMapIter->second)(eventData);
		}

		std::map<std::shared_ptr<EventListener>, EventProcessingType>::iterator listenersIter = mEventListeners.begin();
		for (; listenersIter != mEventListeners.end(); ++listenersIter)
		{
			if ((listenersIter->second == EventProcessingType::BOTH)
			|| (eventData->processingType == EventProcessingType::BOTH)
			|| (listenersIter->second == EventProcessingType::CLIENTSIDE && eventData->processingType == EventProcessingType::CLIENTSIDE)
			|| (listenersIter->second == EventProcessingType::SERVERSIDE && eventData->processingType == EventProcessingType::SERVERSIDE))
			{
				listenersIter->first->processIncomingEvent(eventData);
			}
		}
	}
}

//Sends off all of the queued up network events over the server
//TODO: Server RakNet packet loop to check for incoming packets,
//convert them back into events, and queue them up as local events
//on the other client
void EventSystem::sendQueuedNetworkEvents()
{
	while (!mQueuedNetworkEvents.empty())
	{
		std::shared_ptr<SendableEvent> eventData = mQueuedNetworkEvents.front();
		mQueuedNetworkEvents.pop();

		char* packetData;
		std::size_t packetSize = eventData->allocatePacket(packetData);

		if (gNetManager.mpPacketHandler->isServer())
		{
			if (eventData->isBroadcast)
			{
				gNetManager.mpPacketHandler->broadcast(packetData, packetSize);
			}
			else
			{
				std::shared_ptr<Client> user = nullptr;
				if (gNetManager.mpServer->getClientById(eventData->receiverId, user))
				{
					std::cout << "USERID: " << std::to_string(user->getId()) << std::endl;
					gNetManager.mpPacketHandler->sendToOne(packetData, packetSize, user->getAddress());
				}
			}
		}
		else
		{
			gNetManager.mpPacketHandler->sendToOne(packetData, packetSize, gNetManager.mpPacketHandler->getServerAddress());
		}

		free(packetData);
	}
}