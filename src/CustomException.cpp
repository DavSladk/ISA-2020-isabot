#include "CustomException.h"

CustomException::CustomException(const char *message, ErrorCodes code)
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
const char *CustomException::Message()
{
    return this->errorMessage.c_str();
}