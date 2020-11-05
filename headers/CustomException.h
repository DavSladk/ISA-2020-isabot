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
    MISSING_TOKEN
};

// custom exception class
class CustomException : public std::exception
{
    public:
        CustomException(const std::string message, const ErrorCodes code);
        ErrorCodes Code();
        std::string Message();

    private:
        ErrorCodes errorCode;
        std::string errorMessage;
};

#endif //XSLADK07_CUSTOMEXCEPTION_H