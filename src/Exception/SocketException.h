#include <exception>

class SocketException : public std::exception
{
    const char * mMsg;

    public:
        SocketException(const char * msg) : std::exception()
        {
            mMsg = msg;
        }

        const char * what () const throw ()
        {
            return mMsg;
        }
};