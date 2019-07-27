#include "GameServer.h"

using namespace std;

GameServer::GameServer()
{
	_isRunning = false;
}

GameServer::~GameServer()
{

}

bool GameServer::IsRunning()
{
	return _isRunning;
}

void GameServer::Start(unsigned int port)
{
	_isRunning = true;
}

void GameServer::Stop()
{
	_isRunning = false;
}
