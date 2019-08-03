#ifndef SERVER_H_
#define SERVER_H_

#include <sys/socket.h>
#include <netinet/in.h>
#include <list>

class Server
{
    int mSocket;
    sockaddr_in mAddress;

    std::list<int> mConnections;

    public:
        Server(int port);
        virtual ~Server();

        void CheckAndAcceptNewConnections();
        void CloseConnections();
        void SetOption_AllowAddressReuse();
        void StartListening();
        void StopListening();

        static const int ANY_PROTOCOL = 0;
        static const int SOCKET_ERROR = -1;
        static const int INVALID_SOCKET = SOCKET_ERROR;
        static const int MAX_CONNECTION_REQUESTS = 10;

};

#endif