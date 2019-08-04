#ifndef GAMESERVER_H_
#define GAMESERVER_H_

#include "Server.h"

class GameServer
{
    bool _isRunning;
    Server mServer;

    public:
        GameServer();
        virtual ~GameServer();

        void Start(unsigned int port);
        void Stop();
    
};

#endif