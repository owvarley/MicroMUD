#include <thread>
#include <chrono>
#include <iostream>

#include "GameServer.h"
#include "Server.h"
#include "Exception/SocketException.h"

using namespace std;

GameServer::GameServer() : mServer ()
{
	_isRunning = false;
}

GameServer::~GameServer()
{

}

void GameServer::Start(unsigned int port)
{
	_isRunning = true;

    try
    {
        mServer.StartListening(port);
        
        while (_isRunning )
        {
            mServer.CheckAndAcceptNewConnections();
            _isRunning = false;
        }

        mServer.CloseConnections();
        mServer.StopListening();
    }
    catch(const SocketException& e)
    {
        std::cerr << e.what() << '\n';
    }
}

void GameServer::Stop()
{
	_isRunning = false;
}
