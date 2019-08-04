#include <unistd.h>
#include <sys/socket.h>

#include "Socket.h"
#include "Exception/SocketException.h"

Socket::Socket()
{
    mSocket = INVALID_SOCKET;
    mAddress.sin_family = AF_INET;
    mAddress.sin_addr.s_addr = INADDR_ANY;
}

Socket::Socket(int nSocket, sockaddr_in address)
{
    mSocket = nSocket;
    mAddress = address;
}

Socket::~Socket()
{

}

void Socket::BindAndListen(int MaxLengthOfQueue)
{

    if ( bind(mSocket, (const sockaddr *) &mAddress, sizeof(mAddress)) == SOCKET_ERROR)
        throw SocketException("Unable to bind socket for server.");

    if ( listen(mSocket, MaxLengthOfQueue) == SOCKET_ERROR)
        throw SocketException("Unable to start listening on server.");
}

void Socket::Close()
{
    close(mSocket);
    mSocket = INVALID_SOCKET;
}

void Socket::Create()
{
    if ( (mSocket = socket(AF_INET, SOCK_STREAM, ANY_PROTOCOL)) == INVALID_SOCKET)
        throw SocketException("Unable to create socket for server.");
}

void Socket::SetAllowAddressReuse()
{
    // SO_REUSEADDR takes an int value and expects a boolean value
    int nEnable = 1;

    if ( setsockopt(mSocket, SOL_SOCKET, SO_REUSEADDR, &nEnable, sizeof(nEnable)) == SOCKET_ERROR)
        throw SocketException("Unable to enable address reuse via setsockopt");
}

void Socket::SetPort(unsigned int port)
{
    mAddress.sin_port = htons(port);
}

void Socket::Write(std::string msg)
{
    int nBytesWritten;

    nBytesWritten = write(mSocket, msg.c_str(), msg.length());

    if (nBytesWritten != msg.length())
        throw new SocketException("Socket::Write - not all bytes from message written");
}