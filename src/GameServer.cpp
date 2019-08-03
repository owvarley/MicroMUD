#include <thread>
#include <chrono>
#include <iostream>

#include "GameServer.h"
#include "Server.h"
#include "Exception/SocketException.h"

using namespace std;

GameServer::GameServer(unsigned int port) : mSocket (port)
{
	_isRunning = false;
}

GameServer::~GameServer()
{

}

void GameServer::Start()
{
	_isRunning = true;

    try
    {
        mSocket.StartListening();
        
        while (_isRunning )
        {
            mSocket.CheckAndAcceptNewConnections();
            
            this_thread::sleep_for(chrono::milliseconds(5000));

            _isRunning = false;
        }

        mSocket.CloseConnections();
        mSocket.StopListening();
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
