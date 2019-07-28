#include <thread>
#include <chrono>

#include "GameServer.h"

using namespace std;

GameServer::GameServer()
{
	_isRunning = false;
}

GameServer::~GameServer()
{

}

void GameServer::Start(unsigned int port)
{
	_isRunning = true;

    while (_isRunning
    {
        this_thread::sleep_for(chrono::milliseconds(1000));

        cout << "Stopping GameServer\n\r";
        gameServer->Stop();
        cout << "GameServer stoppped\n\r";
    }
}

void GameServer::Stop()
{
	_isRunning = false;
}
