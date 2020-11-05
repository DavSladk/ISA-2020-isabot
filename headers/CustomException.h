#ifndef XSLADK07_CUSTOMEXCEPTION_H
#define XSLADK07_CUSTOMEXCEPTION_H

#include <exception>
#include <string>

// types of possible custom exceptions
enum ErrorCodes
{
    OPTION_USED_MULTIPLE_TIMES = 1,
    OPTION_REQUIRES_A_ARGUMENT,
    FATAL_ERROR,
    OPTION_UNKNOW,
    OPTION_MISSING,
    NOT_IMPLEMENTED,
    PCAP_OPEN_LIVE_ERROR,
    UNSOPPORTED_LINK_LAYER,
    PCAP_COMPILE_ERROR,
    PCAP_NEXT_ERROR,
    PCAP_SETFILTER_ERROR,
    GETIFADDR_ERROR,
    NO_GLOBAL_IPV6,
    SOCKET_ERROR,
    FORK_ERROR
};

// custom exception class
class CustomException : public std::exception
{
    public:
        CustomException(const char *message, ErrorCodes code);
        ErrorCodes Code();
        const char *Message();

    private:
        ErrorCodes errorCode;
        std::string errorMessage;
};

#endif //XSLADK07_CUSTOMEXCEPTION_H