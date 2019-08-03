#include <exception>

class UnreachableCodeException : public std::exception
{
    const char * mMsg;

    public:
        UnreachableCodeException(const char * msg) : std::exception()
        {
            mMsg = msg;
        }

        const char * what () const throw ()
        {
            return mMsg;
        }
};