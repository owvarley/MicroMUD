#include <iostream>
#include <list>
#include <unistd.h>

#include "Server.h"
#include "Socket.h"
#include "Exception/SocketException.h"

Server::Server() : mSocket()
{

}

Server::~Server()
{
    mConnections.clear();
}

Socket Server::Accept()
{
    int nNewSocket;
    sockaddr_in address;
    socklen_t length;

    length = sizeof address;

    nNewSocket = accept(mSocket.GetFD(), (sockaddr *) &address, &length);

    Socket ret(nNewSocket, address);

    return ret;
}

void Server::CheckAndAcceptNewConnections()
{
    Socket NewConnection = Accept();

    if (!NewConnection.IsValid())
    {
        // No connection to accept
        return;
    }
    else
    {
        NewConnection.Write("Connected to MicroMUD.\n\r"); 
        mConnections.push_back(NewConnection);
    }
}

void Server::CloseConnections()
{
    for (Socket socket : mConnections)
    {
        socket.Write("MicroMUD is shutting down, disconnected.\n\r");
        socket.Close();
    }
}

void Server::StartListening(unsigned int port)
{
    try
    {
        mSocket.Create();
        mSocket.SetPort(port);
        mSocket.SetAllowAddressReuse();
        mSocket.BindAndListen(MAX_CONNECTION_REQUESTS);

        std::cout << "Server running and accepting connections on port " << port << ".\n\r";
    }
    catch(const SocketException& e)
    {
        std::cerr << e.what() << '\n';
        throw e;
    }
}

void Server::StopListening()
{
    mSocket.Close();
    std::cout << "Server terminated.\n\r";
}