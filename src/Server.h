#ifndef SERVER_H_
#define SERVER_H_

#include <sys/socket.h>
#include <list>

#include "Socket.h"

class Server
{
    Socket mSocket;

    std::list<Socket> mConnections;

    public:
        Server();
        virtual ~Server();

        Socket Accept();
        void CheckAndAcceptNewConnections();
        void CloseConnections();
        void StartListening(unsigned int port);
        void StopListening();

        static const int MAX_CONNECTION_REQUESTS = 10;

};

#endif