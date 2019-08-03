#include <iostream>
#include <list>
#include <unistd.h>

#include "Server.h"
#include "Exception/SocketException.h"

Server::Server(int port)
{
    mSocket = INVALID_SOCKET;
    mAddress.sin_family = AF_INET;
    mAddress.sin_addr.s_addr = INADDR_ANY;
    mAddress.sin_port = htons(port);
}

Server::~Server()
{
    mConnections.clear();
}

void Server::CheckAndAcceptNewConnections()
{
    sockaddr_in NewConnection_Address;
    socklen_t NewConnection_Length;
    int NewConnection_Socket;

    NewConnection_Length = sizeof NewConnection_Address;

    NewConnection_Socket = accept(mSocket, (sockaddr *) &NewConnection_Address, &NewConnection_Length);

    if (NewConnection_Socket == INVALID_SOCKET)
    {
        // No connection to accept
        return;
    }
    else
    {
        write(NewConnection_Socket, "Connected to MicroMUD.\n\r", 24); 
        mConnections.push_back(NewConnection_Socket);
    }
}

void Server::CloseConnections()
{
    for (int socket : mConnections)
    {
        write(socket, "MicroMUD is shutting down, disconnected.\n\r", 42);
        close(socket);
    }
}

void Server::SetOption_AllowAddressReuse()
{
    // SO_REUSEADDR takes an int value and expects a boolean value
    int nEnable = 1;

    if ( setsockopt(mSocket, SOL_SOCKET, SO_REUSEADDR, &nEnable, sizeof(nEnable)) == SOCKET_ERROR)
        throw SocketException("Unable to enable address reuse via setsockopt");
}

void Server::StartListening()
{
    try
    {
        if ( (mSocket = socket(AF_INET, SOCK_STREAM, Server::ANY_PROTOCOL)) == INVALID_SOCKET)
            throw SocketException("Unable to create socket for server.");

        SetOption_AllowAddressReuse();

        if ( bind(mSocket, (const sockaddr *) &mAddress, sizeof(mAddress)) == SOCKET_ERROR)
            throw SocketException("Unable to bind socket for server.");

        if ( listen(mSocket, MAX_CONNECTION_REQUESTS) == SOCKET_ERROR)
            throw SocketException("Unable to start listening on server.");

        std::cout << "Server running and accepting connections on port " << mAddress.sin_port << ".\n\r";
    }
    catch(const SocketException& e)
    {
        std::cerr << e.what() << '\n';
        throw e;
    }
}

void Server::StopListening()
{
    close(mSocket);
    mSocket = INVALID_SOCKET;
    
    std::cout << "Server terminated.\n\r";
}
