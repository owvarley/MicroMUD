#ifndef SOCKET_H
#define SOCKET_H

#include <string>
#include <netinet/in.h>

class Socket
{
    int mSocket;
    sockaddr_in mAddress;

    public:
        Socket();
        Socket(int nSocket, sockaddr_in address);
        ~Socket();

        void BindAndListen(int MaxLengthOfQueue);
        void Close();
        void Create();
        int GetFD() { return mSocket; }
        bool IsValid() { return mSocket != INVALID_SOCKET; }
        void SetAllowAddressReuse();
        void SetPort(unsigned int port);
        void Write(std::string);

        static const int ANY_PROTOCOL = 0;
        static const int SOCKET_ERROR = -1;
        static const int INVALID_SOCKET = SOCKET_ERROR;
};

#endif