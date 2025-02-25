//
//  NetworkServer.hpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 8/9/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#ifndef NetworkServer_cpp
#define NetworkServer_cpp

#include <stdio.h>
#include <iostream>
#include <SFML/Network.hpp>
#include "ServerCommunicator.hpp"

/*
 NOTE: If you are a casual user, just focus on the Client and Server classes (i.e. ignore this one).
 */

/*
 The ClientInfo is only used in the NetworkServer class and just serves a container of information about an individaul client (e.g. the vector "clients" consists of ClientInfo objects)
 */
struct ClientInfo {
	sf::IpAddress ip;
	unsigned short udpPort = 0;
	sf::TcpSocket *tcp = nullptr;
};

/*
 NetworkServer handles are the ugly network and thread stuff that someone implementing Server doesn't want to do.
 */
class NetworkServer {
public:
	NetworkServer(ServerCommunicator &com);
	bool networkUpdate();
	void sendTcp(std::string message, sf::IpAddress ip);
	void sendUdp(std::string message, sf::IpAddress ipAddressOfClient);
	virtual bool receivedTcp(std::string message, sf::IpAddress ip, long timeStamp) {};
	virtual bool receivedUdp(std::string message, sf::IpAddress ip, long timeStamp) {};
	virtual void gotNewClient(sf::IpAddress ip) {};
	virtual void lostClient(sf::IpAddress ip) {};
	bool shouldServerContinue();
	long getTime();
private:
	ServerCommunicator &communicator;
	std::vector<ClientInfo> clients;
	void checkForNewClients();
	bool isClientInUpdatedList(sf::TcpSocket *client, std::vector<sf::TcpSocket *>&list);
	bool isInClientList(sf::TcpSocket *ip);
	void sendTcpBySocket(std::string message, sf::TcpSocket *socket);
	sf::UdpSocket udpSocket;
	std::vector<std::string> split(const std::string s, char delim);
};

#endif /* NetworkServer_cpp */
