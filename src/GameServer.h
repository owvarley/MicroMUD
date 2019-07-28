#ifndef GAMESERVER_H_
#define GAMESERVER_H_

class GameServer
{
    bool _isRunning;

    public:
        GameServer();
        virtual ~GameServer();

        void Start(unsigned int port);
        void Stop();
    
};

#endif