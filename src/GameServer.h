#ifndef GAMESERVER_H_
#define GAMESERVER_H_

#include "Server.h"

class GameServer
{
    bool _isRunning;
    Server mSocket;

    public:
        GameServer(unsigned int port);
        virtual ~GameServer();

        void Start();
        void Stop();
    
};

#endif