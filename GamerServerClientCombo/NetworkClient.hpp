//
//  NetworkClient.hpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 8/7/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#ifndef NetworkClient_cpp
#define NetworkClient_cpp

#include <stdio.h>
#include <iostream>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include "ServerCommunicator.hpp"

/*
 * The NetworkClient class is intended to be a singleton that resides inside the
 * Client singleton. It allows simple access to a single server. The server may
 * be on the machine itself, on a local network, or anywhere world-wide.
 * It also serves a side-purpose: allowing for access to the ServerCommunicator
 * singleton.
 */
class NetworkClient {
public:
    NetworkClient(ServerCommunicator& com);
    ~NetworkClient();
    void applicationIsClosing();

    void attemptConnectionToServer(sf::IpAddress serverIpAddress, unsigned short serverPort);
    
    void networkUpdate();
    
    /*
     0 = no connection established
     1 = connection being established
     2 = connection established
     3 = received tcp port from server
     -1 = connection failed
     */
    int getConnectionState();
    
    void sendTcpMessage(std::string message);
    virtual void tcpMessageReceived(std::string message) {};
    virtual void udpMessageReceived(std::string message) {};
    void sendUdpMessage(std::string message);
    
    unsigned short getLocalServerTcpPort();
    
    virtual bool keyPressed(sf::Keyboard::Key keyCode) {};
    virtual bool keyReleased(sf::Keyboard::Key keyCode) {};
    virtual bool mouseMoved(int x, int y) {};
    virtual bool mousePressed(sf::Mouse::Button button, int x, int y) {};
    virtual bool mouseReleased(sf::Mouse::Button button, int x, int y) {};
    virtual bool mouseWheeled(int delta, int x, int y) {};
    virtual bool draw() {};
    virtual bool update() {};
    virtual void connectionStateChanged(int oldState, int newState) {};
private:
    int connectionState = 0;
    sf::TcpSocket tcpSocket;
    sf::UdpSocket udpSocket;
    unsigned short tcpPortOfServer;
    ServerCommunicator &communicator;
    sf::IpAddress ipAddressOfServer;
    unsigned short udpPortOfServer = 0;
    void sendOwnTcpServerMessageToQuit();
};

#endif /* NetworkClient_cpp */
