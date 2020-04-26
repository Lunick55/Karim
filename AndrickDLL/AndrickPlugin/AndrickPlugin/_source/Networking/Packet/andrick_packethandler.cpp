#include <_source/Networking/Packet/andrick_packethandler.h>
#include <_source/Networking/Packet/andrick_packet.h>
#include <_source/Networking/andrick_client.h>
#include <_source/Networking/andrick_server.h>
#include <_source/Utils/network_manager.h>

PacketHandler::PacketHandler() :
	mMaxConnections(0),
	mpPeer(nullptr)
{
	if (gNetManager.mpServer)
	{
		mIsServer = true;//gNetManager.mpServer->isActive;
	}
	else
	{
		mIsServer = false;
	}
}

bool PacketHandler::startup(int maxConnections)
{
	if (!mpPeer)
	{
		mpPeer = RakNet::RakPeerInterface::GetInstance();

		if (mpPeer)
		{
			if (mIsServer)
			{
				mSocketDescriptor = RakNet::SocketDescriptor(sPORT, 0);
			}

			if (mpPeer->Startup(maxConnections, &mSocketDescriptor, 1) == RakNet::StartupResult::RAKNET_STARTED)
			{
				mpPeer->SetMaximumIncomingConnections(maxConnections);
				mpPeer->SetOccasionalPing(true);
				mMaxConnections = maxConnections;

				if (mIsServer)
				{
					mServerAddress = mpPeer->GetSystemAddressFromGuid(mpPeer->GetMyGUID());
				}
				else
				{
					gNetManager.mpClient->setAddress(mpPeer->GetSystemAddressFromGuid(mpPeer->GetMyGUID()));
				}

				return true;
			}
		}
	}

	return false;
}

bool PacketHandler::shutdown()
{
	if (mpPeer)
	{
		mpPeer->Shutdown(500);
		RakNet::RakPeerInterface::DestroyInstance(mpPeer);
		mpPeer = nullptr;

		//gDemoState->mIsOnline = false;
		return true;
	}

	return false;
}

bool PacketHandler::connect(const char* ipAddress)
{
	if (mpPeer)
	{
		RakNet::ConnectionAttemptResult result = mpPeer->Connect(ipAddress, sPORT, 0, 0);
		return (result == RakNet::ConnectionAttemptResult::CONNECTION_ATTEMPT_STARTED);
	}

	return false;
}

bool PacketHandler::disconnect()
{
	if (mpPeer)
	{
		UINT16 i, j = mpPeer->NumberOfConnections();

		for (i = 0; i < j; ++i)
		{
			mpPeer->CloseConnection(mpPeer->GetSystemAddressFromIndex(i), true);
		}

		//gDemoState->mIsOnline = false;
		return true;
	}

	return false;
}

int PacketHandler::processInboundPackets()
{
	RakNet::Packet* packet;
	int packetsProcessed = 0;

	for (packet = mpPeer->Receive(); 
		packet != nullptr; 
		mpPeer->DeallocatePacket(packet), packet = mpPeer->Receive(), ++packetsProcessed)
	{
		//Ignore this for now. We can ask about bitstream later
		//RakNet::BitStream inBitStream(packet->data, packet->length, false);
		//inBitStream.Read(messageId);

		std::vector<std::shared_ptr<Event>> newEvents;

		switch (packet->data[0])
		{
			////////////////////////////////////////////////
			// RAKNET PACKETS                             
			////////////////////////////////////////////////

		case ID_TIMESTAMP:
		{
			std::cout << "BOMB WILL GO OFF IN: " << std::endl;

			switch (packet->data[sizeof(unsigned char) + sizeof(unsigned long)])
			{
			case andrick_ID_BOID_DATA_PUSH_EVENT:
				std::cout << "WE DID IT!" << std::endl;
				break;
			default:
				break;
			}

			break;
		}
		case ID_CONNECTION_REQUEST_ACCEPTED:
		{
			std::cout << "ID_CONNECTION_REQUEST_ACCEPTED" << std::endl;
			break;
		}
		case ID_NEW_INCOMING_CONNECTION:
		{
			std::cout << "ID_NEW_INCOMING_CONNECTION" << std::endl;
			//newEvents.push_back(std::make_shared<NewIncomingConnectionEvent>(packet->systemAddress));
			break;
		}
		case ID_NO_FREE_INCOMING_CONNECTIONS:
			std::cout << "ID_NO_FREE_INCOMING_CONNECTIONS" << std::endl;
			break;
		case ID_DISCONNECTION_NOTIFICATION:
			std::cout << "ID_DISCONNECTION_NOTIFICATION" << std::endl;
			break;
		case ID_CONNECTION_LOST:
			std::cout << "ID_CONNECTION_LOST" << std::endl;
			break;
		case ID_REMOTE_DISCONNECTION_NOTIFICATION:
			std::cout << "ID_REMOTE_DISCONNECTION_NOTIFICATION" << std::endl;
			break;
		case ID_REMOTE_CONNECTION_LOST:
			std::cout << "ID_REMOTE_CONNECTION_LOST" << std::endl;
			break;
		case ID_REMOTE_NEW_INCOMING_CONNECTION:
		{
			std::cout << "ID_REMOTE_NEW_INCOMING_CONNECTION" << std::endl;
			break;
		}
			////////////////////////////////////////////////
			// CUSTOM PACKETS                             
			////////////////////////////////////////////////
		case andrick_ID_CONNECTION_REQUEST_ACCEPTED:///Server sends this to client
		{
			std::cout << "andrick_ID_CONNECTION_REQUEST_ACCEPTED" << std::endl;
			ConnectionRequestAcceptedPacket* requestAcceptedPacket = (ConnectionRequestAcceptedPacket*)packet->data;
			newEvents.push_back(std::make_shared<ConnectionRequestAcceptedEvent>(packet->systemAddress, requestAcceptedPacket->newUserId));
			break;
		}
		case andrick_ID_CONNECTION_ATTEMPT_FAILED:///Server sends this to Client - Server rejected us for some reason
		{
			std::cout << "andrick_ID_CONNECTION_ATTEMPT_FAILED" << std::endl;
			ConnectionRequestFailedPacket* requestFailedPacket = (ConnectionRequestFailedPacket*)packet->data;
			newEvents.push_back(std::make_shared<ConnectionRequestFailedEvent>(packet->systemAddress, requestFailedPacket->errorMessage));
			break;
		}
		case andrick_ID_REQUEST_JOIN_SERVER:///Client sends this to Server
		{
			std::cout << "andrick_ID_REQUEST_JOIN_SERVER" << std::endl;
			RequestJoinServerPacket* requestJoinServerPacket = (RequestJoinServerPacket*)packet->data;
			newEvents.push_back(std::make_shared<ConnectionRequestJoinEvent>(requestJoinServerPacket->userId,
				requestJoinServerPacket->username, false, requestJoinServerPacket->userId));
			break;
		}
		case andrick_ID_JOIN_ACCEPTED:///Server sends this to Joining Client
		{
			std::cout << "andrick_ID_JOIN_ACCEPTED" << std::endl;
			JoinAcceptedPacket* joinAcceptedPacket = (JoinAcceptedPacket*)packet->data;
			newEvents.push_back(std::make_shared<ConnectionJoinAcceptedEvent>(joinAcceptedPacket->username, 
				joinAcceptedPacket->maxUserCount, joinAcceptedPacket->connectedUserCount));
			break;
		}
		case andrick_ID_JOIN_FAILED:///Server sends this to Joining Client
		{
			std::cout << "andrick_ID_JOIN_FAILED" << std::endl;
			JoinFailedPacket* joinFailedPacket = (JoinFailedPacket*)packet->data;
			newEvents.push_back(std::make_shared<ConnectionJoinFailedEvent>(joinFailedPacket->userId, joinFailedPacket->errorMessage));
			break;
		}
		case andrick_ID_USER_JOINED_SERVER:///Server sends this to existing Clients
		{
			std::cout << "andrick_ID_USER_JOINED_SERVER" << std::endl;
			NewUserJoinedServerPacket* userJoinedPacket = (NewUserJoinedServerPacket*)packet->data;
			newEvents.push_back(std::make_shared<ConnectionNewUserJoinedEvent>(userJoinedPacket->userId, userJoinedPacket->username));
			break;
		}
		case andrick_ID_USER_DISCONNECTED:
		{
			std::cout << "andrick_ID_USER_DISCONNECTED" << std::endl;
			UserDisconnectedPacket* userDisconnectedPacket = (UserDisconnectedPacket*)packet->data;
			newEvents.push_back(std::make_shared<UserDisconnectedEvent>(userDisconnectedPacket->userId));
			break;
		}
		case andrick_ID_SEND_MESSAGE:
		{
			MessagePacket* messagePacket = (MessagePacket*)packet->data;
			newEvents.push_back(std::make_shared<MessageEvent>(messagePacket->message));
		}
			////////////////////////////////////////////////
			// UNKNOWN PACKETS                            
			////////////////////////////////////////////////
		default:
		{
			std::cout << "Unknown packet" << std::endl;
			break;
		}
		}

		//for (auto iter = newEvents.begin(); iter != newEvents.end(); ++iter)
		//{
		//	gEventSystem.queueLocalEvent(*iter);
		//}
	}

	return packetsProcessed;
}

bool PacketHandler::broadcast(const char* packetData, std::size_t packetSize) const
{
	int success = mpPeer->Send(
		packetData, 
		(int)packetSize, 
		PacketPriority::IMMEDIATE_PRIORITY, 
		PacketReliability::RELIABLE_ORDERED,
		0, 
		RakNet::UNASSIGNED_SYSTEM_ADDRESS, 
		true);

	return success > 0;
}

bool PacketHandler::sendToOne(const char* packetData, std::size_t packetSize, RakNet::SystemAddress ipAddress) const
{
	int success = mpPeer->Send(
		packetData, 
		(int)packetSize, 
		PacketPriority::IMMEDIATE_PRIORITY, 
		PacketReliability::RELIABLE_ORDERED,
		0, 
		ipAddress, 
		false);

	return success > 0;
}