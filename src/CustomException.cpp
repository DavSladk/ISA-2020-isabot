#include "CustomException.h"

CustomException::CustomException(const std::string message, const ErrorCodes code)
{
    this->errorCode = code;
    this->errorMessage = message;
}

//returns code of custom exception
ErrorCodes CustomException::Code()
{
    return this->errorCode;
}

//returns pointer to message of exception
std::string CustomException::Message()
{
    return this->errorMessage;
}